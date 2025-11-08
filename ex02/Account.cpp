
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
	Account::displayStatus();
	std::cout << ";created\n";
}
Account::~Account(void) {};



int Account::t::getNbAccounts(void)
{
	return (_nbAccounts);
}

int	Account::t::getTotalAmount( void )
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
	this->_amount += deposit;
	_totalAmount += _amount;
	std::cout << _totalAmount << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	if (this->_amount >= withdrawal)
	{
		this->_amount -= withdrawal;
		this->_totalAmount -= _amount;
		return true;
	}
	else
		return false;
}

int		Account::checkAmount( void ) const
{
	return _amount;
}

void	Account::displayStatus( void ) const
{
	_displayTimestamp();
	std::cout << " index:" << _accountIndex;
	std::cout << ";amount:" << Account::checkAmount();
}
void	Account::_displayTimestamp( void )
{
	std::cout << "Aqui vai ser as horas";
}
// [19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
void	Account::displayAccountsInfos( void )
{
	_displayTimestamp();
	std::cout << " accounts:" << Account::getNbAccounts;
	std::cout << ";total:" << Account::getTotalAmount;
	std::cout << ";deposits:" << Account::getNbDeposits;
	std::cout << ";withdrawals:" << Account::getNbWithdrawals << std::endl;
}