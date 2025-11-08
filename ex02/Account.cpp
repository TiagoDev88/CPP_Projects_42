
#include "Account.hpp"
#include <iostream>

//Estas sao as variaveis estaticas
int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account( int initial_deposit ){
	this->_amount = initial_deposit;
	this->_nbDeposits = 0; //talvez seja 0
	this->_nbWithdrawals = 0;
	this->_accountIndex = _nbAccounts++;
	this->_totalAmount += _amount;

	_displayTimestamp();
	std::cout << " index:" << _accountIndex;
	std::cout << ";amount:" << Account::checkAmount();
	std::cout << ";created" << std::endl;

}
Account::~Account(void) 
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex;
	std::cout << ";amount:" << Account::checkAmount();
	std::cout << ";closed" << std::endl;
};



int Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int	Account::getTotalAmount( void )
{
	return (_totalAmount);
}
int	Account::getNbDeposits( void )
{
	return (_totalNbDeposits);
}
int	Account::getNbWithdrawals( void )
{
	return (_totalNbWithdrawals);
}

void	Account::makeDeposit( int deposit )
{
	_displayTimestamp();

	this->_totalNbDeposits++;
	
	std::cout << " index:" << Account::_accountIndex;
	std::cout << ";p_amount:" << Account::checkAmount();
	std::cout << ";deposit:" << deposit;
	this->_amount += deposit;
	this->_totalAmount += deposit;
	this->_nbDeposits++;
	std::cout << ";amount:" << Account::checkAmount();
	std::cout << ";nb_deposits:" << Account::_nbDeposits << std::endl;
}
//[19920104_091532] index:6;p_amount:763;withdrawal:657;amount:106;nb_withdrawals:1
bool	Account::makeWithdrawal( int withdrawal )
{
		_displayTimestamp();

	
	std::cout << " index:" << Account::_accountIndex;
	std::cout << ";p_amount:" << Account::checkAmount();
	std::cout << ";withdrawal:";
	if (withdrawal > checkAmount())
	{
		std::cout << "refused"<< std::endl;
		return (false);
	}
	std::cout << withdrawal;
	this->_amount -= withdrawal;
	this->_totalAmount -= withdrawal;
	this->_nbWithdrawals++;
	std::cout << ";amount:" << Account::checkAmount();
	std::cout << ";nb_withdrawals:" << Account::_nbWithdrawals << std::endl;
	this->_totalNbWithdrawals++;

	return true;
}

int		Account::checkAmount( void ) const
{
	return _amount;
}

void	Account::displayStatus( void ) const
{
	_displayTimestamp();
	std::cout << " index:" << Account::_accountIndex;
	std::cout << ";amount:" << Account::checkAmount();
	std::cout << ";deposits:" << Account::_nbDeposits;
	std::cout << ";withdrawals:" << Account::_nbWithdrawals << std::endl;

}
void	Account::_displayTimestamp( void )
{
	std::cout << "Aqui vai ser as horas";
}
// [19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
void	Account::displayAccountsInfos( void )
{
	_displayTimestamp();
	std::cout << " accounts:" << getNbAccounts();
	std::cout << ";total:" << getTotalAmount();
	std::cout << ";deposits:" << getNbDeposits();
	std::cout << ";withdrawals:" << getNbWithdrawals() << std::endl;
}