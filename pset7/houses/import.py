import sys
import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")

# ensure proper usage
if len(sys.argv) != 2:
    print("Usage: python import.py characters.csv")
    sys.exit()

# open csv
f = open(sys.argv[1])

reader = csv.reader(f)
next(reader, None)

# iterate over each line
for row in reader:
    name = row[0]
    house = row[1]
    birth = row[2]
    # split up name
    n = name.split()
    # if no middle name, insert none value
    if len(n) == 2:
        n.insert(1, None)
    # insert each line of csv into database
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?);", n[0], n[1], n[2], house, birth)

f.close()