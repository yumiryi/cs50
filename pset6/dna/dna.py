import sys
import csv

# ensure proper command-line arguments
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit()

# open files
f = open(sys.argv[1])
g = open(sys.argv[2])

# read files
data = csv.DictReader(f)
sequence = g.read()

# create list of str counts
highestvs = []

def main():
    matchcount = 0
    # calculate str counts for each str
    for i in range(1, len(data.fieldnames)):
        findhighest(data.fieldnames[i])
    # compare str values with each person in database
    for row in data:
        # compare each str value
        for i in range(0, len(highestvs)):
            # if match, increase match count and continue to next str
            if int(row[data.fieldnames[i + 1]]) == int(highestvs[i]):
                matchcount += 1
            # if no match, continue to next person
            else:
                matchcount = 0
                break
        # if all match, print name of person
        if matchcount == len(highestvs):
            print(row["name"])
            return
    # if no one matched, print no match
    print("No match")


def findhighest(x):
    i = 0
    counter = 0
    highest = 0
    # iterate over entire dna sequence
    while i < len(sequence) - (len(x) * 2) - 1:
        sub1 = sequence[i:i + len(x)]
        # find first occurence of str
        if sub1 == x:
            counter += 1
            # count subsequent str occurences
            for j in range(i + len(x), len(sequence) - len(x) - 1, len(x)):
                sub2 = sequence[j:j + len(x)]
                if sub2 == x:
                    counter += 1
                # if no subsequent strs, reset counter and move on in dna sequence
                else:
                    i = j - 1
                    if counter > highest:
                        highest = counter
                    counter = 0
                    break
        i += 1
    # track highest str values
    if highest > 0:
        highestvs.append(highest)

main()