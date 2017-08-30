#include "G1.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include "PBCExceptions.h"

G1 G1::pow2(const Pairing &e, const G1 &base1, const Zr &exp1, const G1 &base2, const Zr &exp2)
{
	G1 gout(e, true);
	G::pow2(gout, base1, exp1, base2, exp2);
	return gout;
}

G1 G1::pow3(const Pairing &e, const G1 &base1, const Zr &exp1, const G1 &base2, const Zr &exp2, const G1 &base3, const Zr &exp3)
{
	G1 gout(e, true);
	G::pow3(gout, base1, exp1, base2, exp2, base3, exp3);
	return gout;
}

//Create and initialize an element
G1::G1(const Pairing &e): G(e){
	if(elementPresent){
		element_init_G1(g, *(pairing_t*)&e.getPairing());
	}else throw UndefinedPairingException();
}

//Create an identity or a random element
G1::G1(const Pairing &e, bool identity): G(e){
	if(elementPresent){
		element_init_G1(g, *(pairing_t*)&e.getPairing());
		if (identity)
		element_set1(g);
		else
		element_random(g);
	}else throw UndefinedPairingException();
}

//Create an element from import
G1::G1(const Pairing &e, const unsigned char *data,
	unsigned short len, bool compressed,
	unsigned short base): G(e){
		if(elementPresent){
			element_init_G1(g, *(pairing_t*)&e.getPairing());
			importElement(data, len, compressed, base);
		}else throw UndefinedPairingException();
	}

	//Create an element from hash
	G1::G1(const Pairing &e, const void *data,
		unsigned short len): G(e){
			if(elementPresent){
				element_init_G1(g, *(pairing_t*)&e.getPairing());
				element_from_hash(g, *(void**)&data, len);
			}else throw UndefinedPairingException();
		}

		//Overriden getElementSize to take care of compressed elements
		unsigned short G1::getElementSize(bool compressed) const{
			if (!elementPresent)
			throw UndefinedElementException();
			else {
				if(compressed)
				return (unsigned short)
				element_length_in_bytes_compressed(*(element_t*)&g);
				else return G::getElementSize();
			}
		}

		//Overriden toString to take care of compressed elements
		string G1::toString(bool compressed) const {
			string str;
			if(compressed){
				if (elementPresent) {
			    std::ostringstream oss;
			    short len = element_length_in_bytes_compressed(*(element_t*)&g);
			    unsigned char data[len];
			    element_to_bytes_compressed(data, *(element_t*)&g);
			    for (int i = 0; i < len; i++) {
			      oss << std::hex << std::setw(2) << std::setfill('0') << +data[i];
			    }
			    str.append(oss.str());
			  }
			} else str.append(G::toString());
			return str;
		}

		string G1::toHexString(bool compressed) const {
			string str;
			if(compressed){
				if (elementPresent) {
			    std::ostringstream oss;
			    short len = element_length_in_bytes_compressed(*(element_t*)&g);
			    unsigned char data[len];
			    element_to_bytes_compressed(data, *(element_t*)&g);
			    for (int i = 0; i < len; i++) {
			      oss << std::hex << std::setw(2) << std::setfill('0') << +data[i];
			    }
			    str.append(oss.str());
			  }
			} else str.append(G::toHexString());
			return str;
		}
