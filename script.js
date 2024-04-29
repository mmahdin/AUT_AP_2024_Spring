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
const btnRoll = document.querySelector('.btn-roll-dice');


const btnHold = document.querySelector('.btn-hold-score');
const btnNewGame = document.querySelector('.btn-new-game');

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

// Roll dice functionality
btnRoll.addEventListener('click', () => {
  console.log("btn-roll-dice clicked ");
  if (playing) {
    // Generate random dice roll
    const dice = Math.floor(Math.random() * 6) + 1;
    console.log(`the dice number is: ${dice}`);

    // Display the dice
    diceEl.src = `dice-${dice}.png`;
    diceEl.classList.remove('hidden');

    // Check if rolled 1
    if (dice !== 1) {
      currentScore += dice;
      document.getElementById(`player-${activePlayer}-current-amount`).textContent = currentScore;
    } else {
      switchPlayer();
    }
  }
});


init();

