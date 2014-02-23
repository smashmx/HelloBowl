#include <iostream>
//#include <string>

class BowlingScore {
	private:
		const int MAX_THROWS = 20; // 21 throws (base 0)
		const int MAX_FRAMES = 9; // 10 frames (base 0)
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

		void calculateScore() {
			for (int current_frame = 0; current_frame < MAX_FRAMES; ++current_frame) {
				int starting_frame = current_frame * 2;
				int throw_1 = throws[starting_frame];
				int throw_2 = throws[starting_frame + 1];
				int current_throws = throw_1 + throw_2;
				if (throw_1 == 10) {
					// Calculate strike
					score_frames[current_frame] = current_throws;
				} else if ((throw_1 + throw_2) == 10) {
					// Calculate spare (Next throw)
					score_frames[current_frame] = current_throws;

					// Add the next if it's available
					int next_throw = starting_frame + 2;
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
};

void assertEqual(int var_a, int var_b, char* func_name) {
	if (var_a != var_b) {
		std::cout << "F" << " " << var_a << " not equal to " << var_b << std::endl;
		std::cout << func_name << std::endl;
	} else {
		std::cout << "." << std::endl;
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
	// Test basic spares
	BowlingScore *bs = new BowlingScore();
	bs->addThrow(10);
	bs->addThrow(10);
	bs->addThrow(4);
	bs->addThrow(2);
	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 46, (char*)__FUNCTION__);
}

void test_perfect_game() {
	BowlingScore *bs = new BowlingScore();
	bs->addSpare();
	bs->addSpare();
	bs->addSpare();
	bs->addSpare();
	bs->addSpare();
	bs->addSpare();
	bs->addSpare();
	bs->addSpare();
	bs->addSpare();
	bs->addThrow(10);
	bs->addThrow(10);
	bs->addThrow(10);

	bs->calculateScore();

	assertEqual(bs->getFinalScore(), 300, (char*)__FUNCTION__);
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
    test_perfect_game();
}

int main() {
	test_suite();

	return 0;
}
