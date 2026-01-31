# Connect4 AI: Minimax limited-depth with various pruning strategies.

This repository contains the implementation of an AI-driven Connect4 game environment. This project explores the application of Negamax algorithms with various prunning strategies and a random algorithm for one vs one gameplay.

This project was developed as part of an AI research project where we entended to answer the question 'How do search depth and pruning strategies influ-
ence runtime efficiency, decision quality and winrate, in a Minimax-based Connect Four agent?'.

## 📌 Project Overview
Connect4 is a classic zero-sum game. This project implements:
- **GameCore:** A robust Connect4 environment with move validation and win detection.
- **Negamax Agents:** An negamax limited-depth agent with various levals of pruning strategies to find the best moves.
- **Opponent** An random algorithm to be one of the baseline opponents to test against.
- **Heuristic** Evaluation of different positions to help our agent when the depth is limited.
- **Helpers** Helper functions

## 🚀 Getting Started

### Installation
1. Clone the repository:
   ```bash
   git clone [https://github.com/Dinisoliv/AGKI_Connect4_DAO_ACS.git](https://github.com/Dinisoliv/AGKI_Connect4_DAO_ACS.git)
   cd AGKI_Connect4_DAO_ACS

### Running the code
1.  Choose the parameters:
    Go to the config.h file, choose the desired Depth, Agent and Opponnent.
2.  Use the command make on the bash commandline.
3.  Run the code using ./connect4_bot

The code will run on the command line, showing the various metrics and the final position, as well as the player that won and all the moves. The metrics will be recorded on a csv file.
