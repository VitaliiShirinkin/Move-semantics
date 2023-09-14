// CMakeProject1.cpp: определяет точку входа для приложения.

#include <iostream>
#include <string>

class big_integer {
	std::string value;

public:
	big_integer() {}

	big_integer(long x) : value(std::to_string(x)) {}

	big_integer(const std::string& str) : value(str) {
		if (!value.length()) {
			this->value = "0";
			return;
		}
		this->value = value.substr();

		int count = 0;
		while (this->value[count] == '0' && this->value.length() - count > 1)
			count++;
		this->value = this->value.substr(count);

		for (size_t i = 0; i < this->value.length(); i++)
			if (this->value[i] < '0' || this->value[i] > '9')
				throw std::exception("invalid character");
	}

	big_integer(big_integer&& other) noexcept
		: value(std::exchange(other.value, nullptr)) {}

	big_integer& operator=(big_integer&& other) noexcept {
		std::swap(value, other.value);
		return *this;
	}

	const std::string& getValue() const {
		return value;
	}

	big_integer operator + (const big_integer& bigInt) const {
		std::string num2 = bigInt.getValue();
		size_t len1 = value.length();
		size_t len2 = num2.length();
		size_t length = 1 + std::max(len1, len2);
		char* res = new char[length + 1];
		res[length - 1] = res[length] = '\0';

		for (size_t i = 0; i < length - 1; i++) {
			int j = length - 1 - i;
			res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0)
				+ ((i < len1) ? (value[len1 - 1 - i] - '0') : 0);
			res[j - 1] = res[j] / 10;
			res[j] = res[j] % 10 + '0';
		}
		res[0] += '0';

		return big_integer(std::string(res));
	}

	big_integer operator * (const big_integer& bigInt) const {
		if (value == "0" || bigInt.getValue() == "0")
			return 0;
		std::string value2 = bigInt.getValue();
		size_t len1 = value.length();
		size_t len2 = value2.length();
		size_t length = len1 + len2 + 1;

		if (length < 10) {
			long res = stol(value) * stol(value2);
			return res;
		}
		else {
			int* a = new int[length];
			int* b = new int[length];
			char* res = new char[length + 1];
			res[length] = '\0';

			for (size_t i = 0; i < length; i++) {
				a[i] = (i < len1) ? (value[len1 - 1 - i] - '0') : 0;
				b[i] = (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;
				res[i] = 0;
			}
			for (size_t i = 0; i < len1; i++) {
				for (size_t j = 0; j < len2; j++) {
					res[length - 1 - (i + j)] += a[i] * b[j];
					res[length - 1 - (i + j + 1)] += res[length - 1 - (i + j)] / 10;
					res[length - 1 - (i + j)] %= 10;
				}
			}
			for (size_t i = 0; i < length; i++)
				res[length - 1 - i] += '0';

			return big_integer(std::string(res));
		}
	}

	friend std::ostream& operator<<(std::ostream& stream, const big_integer& bigInt) {
		return stream << bigInt.getValue();
	}

};

int main(int argc, char** argv) {

	try {
		auto number1 = big_integer("6459134876312645915375645915243562819842157684951435975462712564565467216417897215674812546818645");
		auto number2 = big_integer("5643269487");
		auto result = number1 + number2;
		std::cout << result << std::endl;

		auto result1 = number1 * number2;
		std::cout << result1 << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
