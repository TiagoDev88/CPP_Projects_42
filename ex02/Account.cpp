
#include "Account.hpp"

Account::Account( int initial_deposit ){
	this->_amount = initial_deposit;
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
	return _nbDeposits;
}
int	Account::getNbWithdrawals( void )
{
	return _nbWithdrawals;
}
void	Account::displayAccountsInfos( void )
{

}
void	Account::makeDeposit( int deposit )
{
	this->_amount = deposit;
}
bool	Account::makeWithdrawal( int withdrawal )
{

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