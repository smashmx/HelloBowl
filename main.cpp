#include <iostream>

class BowlingScore {
	private:
		const int MAX_THROWS = 21;
		const int MAX_FRAMES = 10;
		int throws[21] = {};
		int current_throw = 0;

		int score_frames[10] = {};
		int final_score = 0;
	public:
		void addThrow(int pins) {
			if (current_throw < MAX_THROWS) {
				throws[current_throw] = pins;
				++current_throw;
			}
		}

		void addStrike() {
            addThrow(10);
            addThrow(0);
		}

		void addSpare() {
			addThrow(5);
			addThrow(5);
		}

		void addNone() {
			addThrow(0);
			addThrow(0);
		}

		void calculateScore() {
			for (int current_frame = 0; current_frame < MAX_FRAMES; ++current_frame) {
				int starting_throw = current_frame * 2;
				int throw_1 = throws[starting_throw];
				int throw_2 = throws[starting_throw + 1];
				int current_throws = throw_1 + throw_2;
				int next_throw = starting_throw + 2;

				if (throw_1 == 10) {
					// Calculate strike
					score_frames[current_frame] = current_throws;

					// Calculate the next throws to be added as a bonus
					if (current_frame == 9) { // Frame 10
						score_frames[current_frame] += throws[starting_throw + 2];
					} else { // Any other frame
						int next_throws_1 = throws[next_throw];
						int second_bonus_position = 0;

						if (next_throws_1 == 10) {
							// If we have a strike, ignore the second throw and take
							// into account the next throw
							second_bonus_position = starting_throw + 4;
						} else {
							// If we have not a strike, count the second throw of the frame
							second_bonus_position = starting_throw + 3;
						}

						int next_throws_2 = throws[second_bonus_position];

						score_frames[current_frame] += next_throws_1 + next_throws_2;
					}
				} else if ((throw_1 + throw_2) == 10) {
					// Calculate spare (Next throw)
					score_frames[current_frame] = current_throws;

					// Add the next if it's available
					if (next_throw < MAX_THROWS) {
						score_frames[current_frame] += throws[next_throw];
					}
				} else {
					// Calculate normal frame
					score_frames[current_frame] = current_throws;
				}
			}

			for (int current_frame = 0; current_frame < MAX_FRAMES; ++current_frame) {
				final_score += score_frames[current_frame];
			}
		}

		int getFinalScore() {
			return final_score;
		}

		void printScores() {
			std::cout << std::endl;
			for (int current_frame = 0; current_frame < MAX_FRAMES; ++current_frame) {
				std::cout << current_frame << ": " << score_frames[current_frame];
				std::cout << std::endl;
			}
		}
};

void assertEqual(int var_a, int var_b, char* func_name) {
	if (var_a != var_b) {
		std::cout << std::endl << "F " << func_name << " " << var_a << " not equal to " << var_b;
		std::cout << std::endl;
	} else {
		std::cout << ".";
	}
}

void test_1() {
	// Simple throw
	BowlingScore *bs = new BowlingScore();
	bs->addThrow(0);
	bs->addThrow(5);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 5, (char*)__FUNCTION__);
}

void test_2() {
	// 0 points
	BowlingScore *bs = new BowlingScore();
	bs->addThrow(0);
	bs->addThrow(0);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 0, (char*)__FUNCTION__);
}

void test_3() {
	// Simple strike
	BowlingScore *bs = new BowlingScore();
	bs->addThrow(10);
	bs->addThrow(0);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 10, (char*)__FUNCTION__);
}

void test_4() {
	// Test function strike
	BowlingScore *bs = new BowlingScore();
	bs->addStrike();
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 10, (char*)__FUNCTION__);
}

void test_5() {
	// Test function spare
	BowlingScore *bs = new BowlingScore();
	bs->addSpare();
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 10, (char*)__FUNCTION__);
}

void test_6() {
	// Test function spare
	BowlingScore *bs = new BowlingScore();
	bs->addSpare();
	bs->addSpare();
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 25, (char*)__FUNCTION__);
}

void test_7() {
	// Test basic spares
	BowlingScore *bs = new BowlingScore();
	bs->addThrow(7);
	bs->addThrow(3);
	bs->addThrow(4);
	bs->addThrow(2);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 20, (char*)__FUNCTION__);
}

void test_8() {
	// Test strikes in a row
	BowlingScore *bs = new BowlingScore();
	bs->addStrike();
	bs->addStrike();
	bs->addThrow(4);
	bs->addThrow(2);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 46, (char*)__FUNCTION__);
}

void test_9() {
	// Test strikes and some other thows
	BowlingScore *bs = new BowlingScore();
	bs->addStrike();
	bs->addStrike();
	bs->addThrow(4);
	bs->addThrow(6);
	bs->addThrow(2);
	bs->addThrow(0);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 58, (char*)__FUNCTION__);
}

void test_10() {
	// Test the last 3 frames
	BowlingScore *bs = new BowlingScore();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addStrike();
	bs->addStrike();
	bs->addThrow(10);
	bs->addThrow(10);
	bs->addThrow(10);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 90, (char*)__FUNCTION__);
}

void test_11() {
	// More testing in the last 3 frames
	BowlingScore *bs = new BowlingScore();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addStrike();
	bs->addStrike();
	bs->addThrow(0);
	bs->addThrow(10);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 50, (char*)__FUNCTION__);
}

void test_12() {
	// More testing in the last 3 frames
	BowlingScore *bs = new BowlingScore();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addNone();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addThrow(0);
	bs->addThrow(10);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 70, (char*)__FUNCTION__);
}

void test_13() {
	// A real game
	BowlingScore *bs = new BowlingScore();
	bs->addThrow(9);
	bs->addThrow(0);
	bs->addThrow(7);
	bs->addThrow(3);
	bs->addThrow(7);
	bs->addThrow(2);
	bs->addThrow(9);
	bs->addThrow(1);
	bs->addThrow(7);
	bs->addThrow(3);
	bs->addThrow(9);
	bs->addThrow(1);
	bs->addThrow(8);
	bs->addThrow(2);
	bs->addThrow(9);
	bs->addThrow(1);
	bs->addStrike();
	bs->addStrike();
	bs->addThrow(8);
	bs->addThrow(1);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 223, (char*)__FUNCTION__);
}

void test_perfect_game() {
	BowlingScore *bs = new BowlingScore();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addStrike();
	bs->addThrow(10);
	bs->addThrow(10);
	bs->addThrow(10);

	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 300, (char*)__FUNCTION__);
}

void test_dutch200() {
	BowlingScore *bs = new BowlingScore();
	bs->addSpare();
	bs->addStrike();
	bs->addSpare();
	bs->addStrike();
	bs->addSpare();
	bs->addStrike();
	bs->addSpare();
	bs->addStrike();
	bs->addSpare();
	bs->addThrow(10);
	bs->addThrow(0);
	bs->addThrow(10);

	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 200, (char*)__FUNCTION__);
}

void test_suite() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();
    test_9();
    test_10();
    test_perfect_game();
    test_dutch200();
}

int main() {
	test_suite();

	return 0;
}
