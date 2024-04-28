'use strict';

// Pig Game JavaScript Implementation

// Define variables to store player scores and current scores
let scores, currentScore, activePlayer, playing;


// Selecting DOM elements
const score0El = document.getElementById('player-0-score');
const score1El = document.getElementById('player-1-score');
const current0El = document.getElementById('player-0-current-amount');
const current1El = document.getElementById('player-1-current-amount');
const diceEl = document.querySelector('.dice-image');
const player0El = document.querySelector('.player-0');
const player1El = document.querySelector('.player-1');


// Initialize the game
const init = () => {
  scores = [0, 0];
  currentScore = 0;
  activePlayer = 0;
  playing = true;

  score0El.textContent = '0';
  score1El.textContent = '0';
  current0El.textContent = '0';
  current1El.textContent = '0';

  diceEl.classList.add('hidden');
  player0El.classList.add('active-player');
  player1El.classList.remove('active-player');
};

