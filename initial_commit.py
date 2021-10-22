#! /usr/bin/python
import os
import sys
import time
from collections import namedtuple, defaultdict
from datetime import datetime

ALLOWED_EXTS = {".py", ".rb", ".c", ".cpp", ".hpp", ".h", ".sh"}
files_at_day = defaultdict(list)
use_date_at_day = {}

# NOTE: no check at all.
# * No checks whether the repo exist
# * No checks if git command fails
# At the worst it commits and then stops or flood your console
def process_by_date():
    ordered = sorted(files_at_day.iterkeys())
    for day in ordered:
        files_string = (" ").join(files_at_day[day])
        os.system("git add {}".format(files_string))
        os.system("git commit --date=\"{}\" -m \"add files from {}\"".format(use_date_at_day[day], str(day)))


def preprocess():
    global files_at_day
    global use_date_at_day
    cnt = 0

    for root, _, files in os.walk(u"."):
        for filename in files:
            _, ext = os.path.splitext(filename)

            if ext not in ALLOWED_EXTS:
                continue

            path_to_file = os.path.join(root, filename)
            last_modified_time = time.ctime(os.path.getmtime(path_to_file))
            tm = time.localtime(os.path.getmtime(path_to_file))
            key = (tm.tm_year, tm.tm_mon, tm.tm_mday)

            files_at_day[key].append(path_to_file)
            if key not in use_date_at_day:
                use_date_at_day[key] = last_modified_time

            cnt += 1
            sys.stdout.write(".")

    print("\nPreprocessed {}".format(cnt))


if __name__ == "__main__":
    preprocess()
    process_by_date()
