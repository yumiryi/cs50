import sys
import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")

# ensure proper usage
if len(sys.argv) != 2:
    print("Usage: python roster.py House")
    sys.exit()

housename = sys.argv[1]

# query database for students from house
s = db.execute(f"SELECT * FROM students WHERE house = '{housename}' ORDER BY last, first;")

# iterate over each student
for i in range(len(s)):
    first = s[i]["first"]
    middle = s[i]["middle"]
    last = s[i]["last"]
    birth = s[i]["birth"]
    # if no middle name, don't print middle name
    if middle == None:
        print(f"{first} {last}, born {birth}")
    # if middle name, include middle name
    else:
        print(f"{first} {middle} {last}, born {birth}")