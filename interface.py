import argparse
import re
import platform as pltfrm
import subprocess

from mupq import mupq

def parse_arguments():
    parser = argparse.ArgumentParser(description="PQAX Specific Settings")
    parser.add_argument(
        "-p",
        "--platform",
        help="The PQAX platform",
        choices=["cortexa"],
        default="cortexa",
    )
    parser.add_argument(
        "-o",
        "--opt",
        help="Optimization flags",
        choices=["speed", "size", "debug"],
        default="speed",
    )
    parser.add_argument(
        "-l", "--lto", help="Enable LTO flags", default=False, action="store_true"
    )
    parser.add_argument(
        "--no-aio", help="Disable all-in-one compilation", default=False, action="store_true"
    )
    parser.add_argument("-i", "--iterations", default=1, help="Number of iterations for benchmarks")
    return parser.parse_known_args()


def get_platform(args):
    platform = None
    bin_type = 'bin'
    platform = NativePlatform()
    settings = AXSettings(args.platform, args.opt, args.lto, not args.no_aio, args.iterations, bin_type)
    return platform, settings

class NativePlatform(mupq.Platform):

    def run(self, binary_path):
        elf = binary_path.replace("bin", "elf")
        proc = subprocess.run(elf, stdout=subprocess.PIPE)
        if proc.returncode != 0:
            raise Exception("rc != 0. did you forget to enable access to performance counters in usermode?")
        data = proc.stdout
        data = data.decode("utf-8")
        data = re.sub(r'.*={4,}\n', '', data)
        data = re.sub(r'#\n', '', data)
        return data

class AXSettings(mupq.PlatformSettings):
    #: Specify folders to include
    scheme_folders = [  # mupq.PlatformSettings.scheme_folders + [
        ("pqax", "crypto_kem", ""),
        ("pqax", "crypto_sign", ""),
        ("mupq", "mupq/crypto_kem", ""),
        ("mupq", "mupq/crypto_sign", ""),
        ("pqclean", "mupq/pqclean/crypto_kem", "PQCLEAN"),
        ("pqclean", "mupq/pqclean/crypto_sign", "PQCLEAN"),
    ]

    def __init__(self, platform, opt="speed", lto=False, aio=False, iterations=1, binary_type='bin'):
        """Initialize with a specific platform"""
        self.binary_type = binary_type
        optflags = {"speed": [], "size": ["OPT_SIZE=1"], "debug": ["DEBUG=1"]}
        if opt not in optflags:
            raise ValueError(f"Optimization flag should be in {list(optflags.keys())}")
        super(AXSettings, self).__init__()
        self.makeflags = [f"PLATFORM={platform}"]
        self.makeflags += [f"MUPQ_ITERATIONS={iterations}"]
        self.makeflags += optflags[opt]


        if pltfrm.machine() != "aarch64":
            self.skip_list = [{'implementation': 'aarch64'}]

        if lto:
            self.makeflags += ["LTO=1"]
        else:
            self.makeflags += ["LTO="]
        if aio:
            self.makeflags += ["AIO=1"]
        else:
            self.makeflags += ["AIO="]
