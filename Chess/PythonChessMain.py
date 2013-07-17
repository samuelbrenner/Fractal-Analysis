#! /usr/bin/env python
"""
 Project: Python Chess
 File name: PythonChessMain.py
 Description:  Chess for player vs. player, player vs. AI, or AI vs. AI.
	Uses Tkinter to get initial game parameters.  Uses Pygame to draw the 
	board and pieces and to get user mouse clicks.  Run with the "-h" option 
	to get full listing of available command line flags.  
	
 Copyright (C) 2009 Steve Osborne, srosborne (at) gmail.com
 http://yakinikuman.wordpress.com/
 *******
 This program is free software; you can redistribute it and/or modify 
 it under the terms of the GNU General Public License as published by 
 the Free Software Foundation; either version 2 of the License, or 
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful, but 
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *******
 Version history:

 v 0.7 - 27 April 2009.  Dramatically lowered CPU usage by using 
   "pygame.event.wait()" rather than "pygame.event.get()" in
   ChessGUI_pygame.GetPlayerInput().
 
 v 0.6 - 20 April 2009.  Some compatibility fixes: 1) Class: instead of 
   Class(), 2) renamed *.PNG to *.png, 3) rendered text with antialias flag on.  
   Also changed exit() to sys.exit(0). (Thanks to tgfcoder from pygame website 
   for spotting these errors.)
 
 v 0.5 - 16 April 2009.  Added new AI functionality - created 
   "ChessAI_defense" and "ChessAI_offense."  Created PythonChessAIStats 
   class for collecting AI vs. AI stats.  Incorporated Python module 
   OptionParser for better command line parsing.
   
 v 0.4 - 14 April 2009.  Added better chess piece graphics from Wikimedia
   Commons.  Added a Tkinter dialog box (ChessGameParams.py) for getting
   the game setup parameters.  Converted to standard chess notation for 
   move reporting and added row/col labels around the board.
 
 v 0.3 - 06 April 2009.  Added pygame graphical interface.  Includes
   addition of ScrollingTextBox class.
   
 v 0.2 - 04 April 2009.  Broke up the program into classes that will
   hopefully facilitate easily incorporating graphics or AI play.
 
 v 0.1 - 01 April 2009.  Initial release.  Draws the board, accepts
   move commands from each player, checks for legal piece movement.
   Appropriately declares player in check or checkmate.

 Possible improvements:
   - Chess Rules additions, ie: Castling, En passant capture, Pawn Promotion
   - Better AI
   - Network play
   
"""

from ChessBoard import ChessBoard
from ChessPlayer import ChessPlayer
from attemptAtGrid import ChessGUI_pygame
from ChessGameParams import TkinterGameSetupParams

from optparse import OptionParser
import time

class PythonChessMain:
	def __init__(self,options):
		if options.debug:
			self.Board = ChessBoard(2)
			self.debugMode = True
		else:
			self.Board = ChessBoard(0)#0 for normal board setup; see ChessBoard class for other options (for testing purposes)
			self.debugMode = False

		
	def SetUp(self,options):
		#gameSetupParams: Player 1 and 2 Name, Color, Human/AI level
	
		self.guitype = 'pygame'
		if options.old:
			self.Gui = ChessGUI_pygame(0)
		else:
			self.Gui = ChessGUI_pygame(1)
			
	def MainLoop(self):
		for x in range (10):
			self.Board.generate()
			self.Board.GetState()
			self.Gui.Draw(board)	
			time.sleep(2)
		self.Gui.EndGame(board)
		

parser = OptionParser()
parser.add_option("-d", dest="debug",
				  action="store_true", default=False, help="Enable debug mode (different starting board configuration)")
parser.add_option("-t", dest="text",
				  action="store_true", default=False, help="Use text-based GUI")
parser.add_option("-o", dest="old",
				  action="store_true", default=False, help="Use old graphics in pygame GUI")
parser.add_option("-p", dest="pauseSeconds", metavar="SECONDS",
				  action="store", default=0, help="Sets time to pause between moves in AI vs. AI games (default = 0)")


(options,args) = parser.parse_args()

game = PythonChessMain(options)
game.SetUp(options)
game.MainLoop()


	
