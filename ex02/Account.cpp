
#include "Account.hpp"

int _accountIndex = 0;

Account::Account( int initial_deposit ){
	this->_amount = initial_deposit;
	this->_nbDeposits = 1;
	this->_nbWithdrawals = 0;
	this->_accountIndex++;
}
Account::~Account(void) {};


int Account::getNbAccounts(void)
{
	return _nbAccounts;
}

int	Account::getTotalAmount( void )
{
	return _totalAmount;
}
int	Account::getNbDeposits( void )
{
	return _totalNbDeposits;
}
int	Account::getNbWithdrawals( void )
{
	return _totalNbWithdrawals;
}

void	Account::makeDeposit( int deposit )
{
	this->_amount += deposit;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	if (this->_amount >= withdrawal)
	{
		this->_amount -= withdrawal;
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

}
void	Account::_displayTimestamp( void )
{

}

void	Account::displayAccountsInfos( void )
{

}