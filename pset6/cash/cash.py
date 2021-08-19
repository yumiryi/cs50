import cs50

# prompt user for input
while True:
    n = cs50.get_float("Change owed: ")
    if n >= 0:
        break

# convert dollars to cents
cents = round(n * 100)
coins = 0

# count quarters
while cents >= 25:
    cents -= 25
    coins += 1

# count dimes
while cents >= 10:
    cents -= 10
    coins += 1

# count nickels
while cents >= 5:
    cents -= 5
    coins += 1

# count pennies and print coins
print(f"{coins + cents}")