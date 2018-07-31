# Alien Isolation

Goal - Use IPC to have two processes talk to each other but don't use pipes

This is a basic model of the alien isolation game. When the player program runs, it awaits a "guess" from the alien using a message queue. When the alien is launched it guesses where the player is at and sends the guess to the player. The player then
determines if the guess was too high or too low and sends it to the alien. The alien then makes a more educated guess and
moves closer and closer to the player until the player is found. This inter processor communication uses a message queue
for the two programs to send data to each other.
