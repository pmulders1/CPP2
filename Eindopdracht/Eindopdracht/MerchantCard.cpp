#include "MerchantCard.h"



MerchantCard::MerchantCard() : CharacterCard("Merchant", CharacterType::MERCHANT)
{
	this->set_discription("Recieves one extra gold, Recieves gold from commercial buildings.");
}

void MerchantCard::execute() {

}

MerchantCard::~MerchantCard()
{
}
