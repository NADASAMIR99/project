# File name : CS112_A1_T2_2_20230441
# Purpose : A game (NUMBER SCRABBLE): in which each player chosen a number from mainlist and when there exist three numbers there subtraction equal 15 counter player win else draw
#Author : Dr Mohammed El-Ramly and Nada Samir 
# ID: 20230441
from itertools import combinations

def winnercheck(number):  # to find the possible sums of the selected numbers so far and see if they add up to 15
    if len(number) >= 3:
        for limit in range(3, len(number) + 1):
            for comb in combinations(number, limit):
                if sum(comb) == 15 and len(comb) == 3:
                    return True
mainlist = [1, 2, 3, 4, 5, 6, 7, 8, 9]
print(mainlist)
player1_numbers = []
player2_numbers = []
player = 1
#welcome message and available numbers
print("welcome to the game!")
print(f"available numbers are {mainlist}")
print(f"player1_numbers are []")
print(f"player2_numbers are []")
while True:
    chose_nummber = int(input(f"player {player},please choose an available number from {mainlist}"))
    #chek if the number is correct
    while chose_nummber not in mainlist:
        chose_nummber = int(input(f"the number {chose_nummber} is not available, please select one from {mainlist}: "))
    #remove chosen element from mainlist
    mainlist.remove(chose_nummber)
    # if no one wins then draw
    if len(mainlist) == 0:
        print("DRAW")
        quit()
    #adding the number to the list of the player
    if player == 1:
        player1_numbers.append(chose_nummber)
        if winnercheck(player1_numbers):
            print("player1 wins")
            quit() #Exit the program if there
    elif player == 2:
        player2_numbers.append(chose_nummber)
        if winnercheck(player2_numbers):
            print("player2 wins")
            quit()  # Exist the program if there is a winner
    if player == 1: player = 2
    else: player = 1