// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.
 @x // starting point
  M=0 // x at upper left corner

(loop)
@KBD 
D=M 
@black
D;JGT
@white
0;JMP 

(black)
@x
D=M
@8192 
D=D-A
@loop
D;JGE 
@x
D=M
@SCREEN
A=A+D 
M=-1 
@x
M=M+1 
@loop
0;JMP 
 
(white)
@x
D=M 
@loop
D;JLT 
@x
D=M
@SCREEN
A=A+D 
M=0 
@x
M=M-1 
@loop
0;JMP 


(end)
@end
0;JMP 
