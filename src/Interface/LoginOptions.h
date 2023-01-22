#include <iomanip>
#include <iostream>

class LoginOptions
{
public:
	enum class LoginType
	{
		USER,
		MANAGER
	};

	std::string Login_firstname{};
	int			Login_regNo{};
	LoginType	MainOptions();
	std::string getLoginOptions();
	std::string inputName();
	int			inputregNo();
	int			inputManagerregNo();

private:
	void		DisplayLoginOption();
};