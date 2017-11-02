#include "tcnullstock.h"

tcNullStock tcNullStock::NullStock;

tcNullStock::tcNullStock()
{
}

QString tcNullStock::GetStockName()
{
	return "";
}

QString tcNullStock::GetDescription()
{
	return "";
}
