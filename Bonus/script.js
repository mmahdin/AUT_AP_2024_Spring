'use strict';

// Pig Game JavaScript Implementation

// Define variables to store player scores and current scores
let scores, currentScore, playing, currentPlayer;


// Selecting DOM elements
const diceEl = document.querySelector('.dice-image');
const player0El = document.querySelector('.player-0');
const player1El = document.querySelector('.player-1');
const btnRoll = document.querySelector('.btn-roll-dice');
const btnHold = document.querySelector('.btn-hold-score');
const btnNewGame = document.querySelector('.btn-new-game');
const body = document.body || document.documentElement;

const windScore = 100;

// Initialize the game
const init = () => {
  scores = [0, 0];
  currentScore = 0;
  currentPlayer = 0;
  playing = true;

  document.getElementById(`player-0-current-amount`).textContent = '0';
  document.getElementById(`player-1-current-amount`).textContent = '0';
  document.getElementById('player-0-score').textContent = '0';
  document.getElementById('player-1-score').textContent = '0';

  // diceEl.classList.add('hidden');
  diceEl.style.opacity = '0';
  player0El.classList.add('active-player');
  player1El.classList.remove('active-player');

  btnHold.addEventListener('click', hold);
  btnRoll.addEventListener('click', roolDice);

  body.style.backgroundColor = '#69cbc0';

  enableButtons();
};

// Hold btn functionality
btnHold.addEventListener('click', hold);

function roolDice(){
  console.log("btn-roll-dice clicked ");
  if (playing) {
    // Generate random dice roll
    const dice = Math.floor(Math.random() * 6) + 1;
    console.log(`the dice number is: ${dice}`);

    // Display the dice
    diceEl.src = `dice-${dice}.png`;
    // diceEl.classList.remove('hidden');
    diceEl.style.opacity = '1';

    // Check if rolled 1
    if (dice !== 1) {
      currentScore += dice;
      if(checkScore()){
        playerWin();
      }else {
      setCurrentScore();
      }
    } else {
      // scores[currentPlayer] = 0;
      currentScore = 0;
      // updatePlayerScore();
      switchPlayer();
    }
  }
}

// Roll dice functionality
btnRoll.addEventListener('click', roolDice);


function setCurrentScore(){
  document.getElementById(`player-${currentPlayer}-current-amount`).textContent = currentScore;
}

function updatePlayerScore(){
  scores[currentPlayer] += currentScore;
  document.getElementById(`player-${currentPlayer}-score`).textContent = scores[currentPlayer];
  currentScore = 0;
}

function togglePlayers(){
  currentPlayer = (currentPlayer + 1) % 2;
  player0El.classList.toggle('active-player');
  player1El.classList.toggle('active-player');
}

function checkScore(){
  if (currentScore + scores[currentPlayer] >= windScore){return 1;}
  else{return 0;} 
}

function switchPlayer(){
  currentScore = 0;
  setCurrentScore();
  togglePlayers();
}

function hold(){
  updatePlayerScore();
  if(checkScore()){
    playerWin();
  }else {
    switchPlayer();
  }
}

function playerWin(){
  playing = false;
  updatePlayerScore();
  // diceEl.classList.add('hidden');
  diceEl.style.opacity = '0';
  document.getElementById(`player-${currentPlayer}-current-amount`).textContent = '🎉';
  body.style.backgroundColor = '#E64980';
  btnHold.removeEventListener('click', hold);
  btnRoll.removeEventListener('click', roolDice);
  disableButtons();
}

function disableButtons() {
  btnHold.style.backgroundColor = 'gray';
  btnRoll.style.backgroundColor = 'gray';
}

function enableButtons() {
  btnHold.style.backgroundColor = '#e64980';
  btnRoll.style.backgroundColor = '#228be6';
}


btnNewGame.addEventListener('click', init);

init();

