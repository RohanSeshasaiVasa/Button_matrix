#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Keypad.h>

#define LED_PIN 6
#define NUM_LEDS 16

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ---------- KEYPAD ----------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {7,8,9,10};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const char* rowLabels[ROWS] = {"R4", "R3", "R2", "R1"};
const char* colLabels[COLS] = {"C1", "C2", "C3", "C4"};

// LED order for a 4x4 matrix. Adjust this table if your NeoPixels are wired differently.
const int ledMap[ROWS][COLS] = {
  {3, 2, 1, 0},
  {4, 5, 6, 7},
  {11, 10, 9, 8},
  {12, 13, 14, 15}
};

int obstacleRows[ROWS];
int obstacleCols[ROWS];
int obstacleIndices[ROWS];
int startRow = -1, startCol = -1, startIdx = -1;
int endRow = -1, endCol = -1, endIdx = -1;
int blinkingIdx = -1;
bool blinkOn = false;
unsigned long lastBlinkToggle = 0;
uint8_t blinkR = 0, blinkG = 255, blinkB = 0;
bool pathInProgress = false;
int currentRow = -1, currentCol = -1, currentIdx = -1;
int targetRow = -1, targetCol = -1, targetIdx = -1;
bool gameEnded = false;

bool isAdjacent(int r1, int c1, int r2, int c2) {
  int manhattan = abs(r1 - r2) + abs(c1 - c2);
  return manhattan == 1;
}

bool isObstacleCell(int row, int col) {
  for (int i = 0; i < ROWS; i++) {
    if (obstacleRows[i] == row && obstacleCols[i] == col) {
      return true;
    }
  }
  return false;
}

bool hasPathBetween(int sr, int sc, int tr, int tc) {
  bool visited[ROWS][COLS] = {false};
  int qRow[ROWS * COLS];
  int qCol[ROWS * COLS];
  int head = 0;
  int tail = 0;

  qRow[tail] = sr;
  qCol[tail] = sc;
  tail++;
  visited[sr][sc] = true;

  const int dr[4] = {-1, 1, 0, 0};
  const int dc[4] = {0, 0, -1, 1};

  while (head < tail) {
    int r = qRow[head];
    int c = qCol[head];
    head++;

    if (r == tr && c == tc) {
      return true;
    }

    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) continue;
      if (visited[nr][nc]) continue;
      if (isObstacleCell(nr, nc)) continue;

      visited[nr][nc] = true;
      qRow[tail] = nr;
      qCol[tail] = nc;
      tail++;
    }
  }

  return false;
}

bool isObstacleIndex(int idx) {
  for (int i = 0; i < ROWS; i++) {
    if (obstacleIndices[i] == idx) {
      return true;
    }
  }
  return false;
}

void generateObstaclePreview() {
  bool usedCols[COLS] = {false};

  for (int row = 0; row < ROWS; row++) {
    int col;
    do {
      col = random(0, COLS);
    } while (usedCols[col]);

    usedCols[col] = true;
    obstacleRows[row] = row;
    obstacleCols[row] = col;
    obstacleIndices[row] = ledMap[row][col];

    Serial.print("Obstacle: O");
    Serial.print(row + 1);
    Serial.print(col + 1);
    Serial.println("LED");
  }
}

void showObstaclePreview() {
  strip.clear();
  for (int i = 0; i < ROWS; i++) {
    strip.setPixelColor(obstacleIndices[i], strip.Color(255, 0, 0));
  }
  strip.show();
  delay(5000);
}

void generateStartEndPreview() {
  while (true) {
    startRow = random(0, ROWS);
    startCol = random(0, COLS);

    endRow = random(0, ROWS);
    endCol = random(0, COLS);

    if (startRow == endRow && startCol == endCol) continue;
    if (isObstacleCell(startRow, startCol) || isObstacleCell(endRow, endCol)) continue;
    if (isAdjacent(startRow, startCol, endRow, endCol)) continue;
    if (!hasPathBetween(startRow, startCol, endRow, endCol)) continue;

    startIdx = ledMap[startRow][startCol];
    endIdx = ledMap[endRow][endCol];
    break;
  }

  Serial.print("Start: S");
  Serial.print(startRow + 1);
  Serial.print(startCol + 1);
  Serial.println("LED");

  Serial.print("End: E");
  Serial.print(endRow + 1);
  Serial.print(endCol + 1);
  Serial.println("LED");
}

void showRoundBoard() {
  strip.clear();

  strip.setPixelColor(startIdx, strip.Color(0, 255, 0));
  strip.setPixelColor(endIdx, strip.Color(0, 255, 0));
  strip.show();
}

void printRoundSummary() {
  Serial.print("Round -> Obstacles: ");
  for (int i = 0; i < ROWS; i++) {
    Serial.print("O");
    Serial.print(obstacleRows[i] + 1);
    Serial.print(obstacleCols[i] + 1);
    Serial.print("LED");
    if (i < ROWS - 1) Serial.print(",");
  }

  Serial.print(" | Start: S");
  Serial.print(startRow + 1);
  Serial.print(startCol + 1);
  Serial.print("LED");

  Serial.print(" | End: E");
  Serial.print(endRow + 1);
  Serial.print(endCol + 1);
  Serial.println("LED");
}

void setupRoundPreview() {
  generateObstaclePreview();
  showObstaclePreview();
  generateStartEndPreview();
  printRoundSummary();
  showRoundBoard();
}

void clearBoard() {

  strip.clear();
  strip.show();
}

void showSmileySymbol(uint8_t r, uint8_t g, uint8_t b) {
  strip.clear();

  // 4x4 smiley face pattern (eyes + smile curve)
  const int smileyPattern[][2] = {
    {0, 1}, {0, 2},
    {1, 0}, {1, 3},
    {2, 0}, {2, 3},
    {3, 1}, {3, 2}
  };

  for (unsigned int i = 0; i < sizeof(smileyPattern) / sizeof(smileyPattern[0]); i++) {
    int row = smileyPattern[i][0];
    int col = smileyPattern[i][1];
    int idx = ledMap[row][col];
    strip.setPixelColor(idx, strip.Color(r, g, b));
  }

  strip.show();
}

void blinkObstacleHit(int idx) {
  for (int i = 0; i < 6; i++) {
    strip.clear();
    strip.setPixelColor(idx, strip.Color(255, 0, 0));
    strip.show();
    delay(140);

    strip.clear();
    strip.show();
    delay(120);
  }
}

void showRoundBoardWithBlink() {
  strip.clear();

  bool showStart = !(blinkingIdx == startIdx && !blinkOn);
  bool showEnd = !(blinkingIdx == endIdx && !blinkOn);

  if (showStart) {
    strip.setPixelColor(startIdx, strip.Color(0, 255, 0));
  }
  if (showEnd) {
    strip.setPixelColor(endIdx, strip.Color(0, 255, 0));
  }

  if (blinkingIdx != -1 && blinkOn) {
    strip.setPixelColor(blinkingIdx, strip.Color(blinkR, blinkG, blinkB));
  }

  strip.show();
}

void updateBlinking() {
  if (blinkingIdx == -1) return;

  if (millis() - lastBlinkToggle >= 250) {
    lastBlinkToggle = millis();
    blinkOn = !blinkOn;
    showRoundBoardWithBlink();
  }
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n\n========== ARDUINO STARTUP ==========");
  Serial.println("Keypad monitoring active. Press any button...");
  Serial.println("===================================\n");
  strip.begin();
  strip.setBrightness(70);
  strip.show();
  randomSeed(analogRead(A0));
}

// Convert keypad key → row/column position
bool getKeyPosition(char key, int &row, int &col) {
  switch(key) {
    case '1': row = 0; col = 0; return true;
    case '2': row = 0; col = 1; return true;
    case '3': row = 0; col = 2; return true;
    case 'A': row = 0; col = 3; return true;
    case '4': row = 1; col = 0; return true;
    case '5': row = 1; col = 1; return true;
    case '6': row = 1; col = 2; return true;
    case 'B': row = 1; col = 3; return true;
    case '7': row = 2; col = 0; return true;
    case '8': row = 2; col = 1; return true;
    case '9': row = 2; col = 2; return true;
    case 'C': row = 2; col = 3; return true;
    case '*': row = 3; col = 0; return true;
    case '0': row = 3; col = 1; return true;
    case '#': row = 3; col = 2; return true;
    case 'D': row = 3; col = 3; return true;
  }
  return false;
}

// ---------- MAIN LOOP ----------
void loop() {
  if (gameEnded) {
    delay(50);
    return;
  }

  static bool roundPreviewDone = false;

  if (!roundPreviewDone) {
    Serial.println("Step 1: Obstacle preview (5 seconds)");
    setupRoundPreview();
    Serial.println("Step 2: Start/End LEDs active");
    Serial.println("Step 3: Start from S/E and move to the other with adjacent keys only.");
    Serial.println("Avoid obstacle LEDs. Each accepted key will blink.\n");
    blinkingIdx = -1;
    blinkOn = false;
    lastBlinkToggle = millis();
    pathInProgress = false;
    currentRow = -1;
    currentCol = -1;
    currentIdx = -1;
    targetRow = -1;
    targetCol = -1;
    targetIdx = -1;
    roundPreviewDone = true;
  }

  static unsigned long lastHeartbeat = 0;
  if (millis() - lastHeartbeat >= 1000) {
    lastHeartbeat = millis();
    Serial.println("waiting for key press...");
  }

  updateBlinking();

  char key = keypad.getKey();

  if (key) {
    Serial.print("Raw key: ");
    Serial.println(key);

    int row = 0, col = 0;
    if (!getKeyPosition(key, row, col)) {
      Serial.println("Unknown key");
      return;
    }

    int idx = ledMap[row][col];
    
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print(" | Row: ");
    Serial.print(rowLabels[row]);
    Serial.print(" | Col: ");
    Serial.print(colLabels[col]);
    Serial.print(" | LED[");
    Serial.print(row);
    Serial.print("][");
    Serial.print(col);
    Serial.println("]");

    if (!pathInProgress) {
      if (isObstacleIndex(idx)) {
        Serial.println("Obstacle selected. Press START or END LED to begin path.");
        return;
      }

      if (idx != startIdx && idx != endIdx) {
        Serial.println("Press START or END LED to begin path.");
        return;
      }

      pathInProgress = true;
      currentRow = row;
      currentCol = col;
      currentIdx = idx;

      if (idx == startIdx) {
        targetRow = endRow;
        targetCol = endCol;
        targetIdx = endIdx;
        Serial.println("Path started at START LED.");
      } else {
        targetRow = startRow;
        targetCol = startCol;
        targetIdx = startIdx;
        Serial.println("Path started at END LED.");
      }

      blinkingIdx = idx;
      blinkR = 0;
      blinkG = 255;
      blinkB = 0;
      blinkOn = true;
      lastBlinkToggle = millis();
      showRoundBoardWithBlink();
      Serial.println("Now press adjacent safe LEDs toward target.");
      return;
    }

    if (isObstacleIndex(idx)) {
      Serial.println("Obstacle hit during traversal.");
      Serial.println("Blinking obstacle and showing RED smiley.");
      blinkObstacleHit(idx);
      showSmileySymbol(255, 0, 0);
      Serial.println("Game ended.");
      gameEnded = true;
      return;
    }

    if (!isAdjacent(currentRow, currentCol, row, col)) {
      Serial.println("Invalid move: press an adjacent LED only.");
      return;
    }

    currentRow = row;
    currentCol = col;
    currentIdx = idx;

    blinkingIdx = idx;
    if (idx == startIdx || idx == endIdx) {
      blinkR = 0;
      blinkG = 255;
      blinkB = 0;
    } else {
      blinkR = 0;
      blinkG = 255;
      blinkB = 0;
    }
    blinkOn = true;
    lastBlinkToggle = millis();
    showRoundBoardWithBlink();

    if (idx == targetIdx) {
      Serial.println("Reached target LED successfully.");
      Serial.println("Showing CORRECT symbol.");
      showSmileySymbol(0, 255, 0);
      delay(3000);
      clearBoard();
      Serial.println("Restarting game with a new round.");
      roundPreviewDone = false;
      return;
    }

    Serial.println("Good move. Continue...");
  } else {
    delay(10);
  }
}
