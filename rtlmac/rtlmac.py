#!/usr/bin/env python3
import argparse, random, subprocess, sys, re, os


def generate_mac():
    mac = [
        0x02,
        random.randint(0x00, 0x7F),
        random.randint(0x00, 0xFF),
        random.randint(0x00, 0xFF),
        random.randint(0x00, 0xFF),
        random.randint(0x00, 0xFF),
    ]
    return ":".join(f"{x:02x}" for x in mac)


def is_valid_mac(mac):
    return re.fullmatch(r"^([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}$", mac) is not None


def check_root() -> bool:
    if os.geteuid():
        print("This script must be run as root!", file=sys.stderr)
        return False
    return True


import os
from pathlib import Path


def blacklist_realtek_modules() -> bool:
    modules = ["r8169", "r8168", "r8125", "r8101"]
    blacklist_path = Path("/etc/modprobe.d/realtek-blacklist.conf")

    # Read currently loaded modules
    with open("/proc/modules") as f:
        loaded = {line.split()[0] for line in f if any(m in line for m in modules)}

    # Skip if none are loaded
    if not loaded:
        return True

    # Read current blacklist file contents if exists
    existing_blacklist = set()
    if blacklist_path.exists():
        with open(blacklist_path) as f:
            for line in f:
                if line.startswith("blacklist"):
                    parts = line.strip().split()
                    if len(parts) == 2:
                        existing_blacklist.add(parts[1])

    # Determine new modules to blacklist
    new_blacklist = loaded - existing_blacklist

    if new_blacklist:
        with open(blacklist_path, "a") as f:
            for mod in new_blacklist:
                f.write(f"blacklist {mod}\n")
        return False

    return True


def main():
    if not check_root():
        sys.exit(1)

    parser = argparse.ArgumentParser(description="Update Realtek NIC MAC Address.")
    parser.add_argument("--mac", help="Specify a MAC address to use.")

    args = parser.parse_args()
    mac = args.mac if args.mac else generate_mac()

    if not blacklist_realtek_modules():
        print("Module blacklist installed, press enter to reboot.")
        try:
            input()
        except EOFError:
            pass
        except KeyboardInterrupt:
            pass
        subprocess.run(["reboot"], check=True)
    else:
        os.remove("/etc/modprobe.d/realtek-blacklist.conf")

    if not is_valid_mac(mac):
        print(f"Invalid MAC address: {mac}", file=sys.stderr)
        sys.exit(1)

    print(
        ("--- NOTICE " * 4)
        + "---\nThis operation can only be performed a handful of times."
        + '\n\nType "YES" (without the quotes) if you are certain.\n'
        + f"MAC: {mac}\n"
        + ("--- NOTICE " * 4)
        + "---"
    )
    mac = mac.replace(":", "")

    try:
        txt = input("> ")
        if txt == "YES":
            print("Acknowledged, continuing.")
            try:
                os.chdir("/opt/rtnicpg")
                subprocess.run(["/opt/rtnicpg/pgload.sh"], check=True)
                subprocess.run(
                    [
                        "/opt/rtnicpg/rtnicpg-aarch64-linux-gnu",
                        "/efuse",
                        "/nodeid",
                        mac,
                    ],
                    check=True,
                )
                print("Done, press enter to reboot.")
                try:
                    input()
                except EOFError:
                    pass
                except KeyboardInterrupt:
                    pass
                subprocess.run(["reboot"], check=True)
            except subprocess.CalledProcessError as e:
                print(f"Command failed: {e}", file=sys.stderr)
                sys.exit(e.returncode)
    except EOFError:
        print()
    except KeyboardInterrupt:
        print()


if __name__ == "__main__":
    main()
