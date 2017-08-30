#include "G1.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include "PBCExceptions.h"
#include "openssl/objects.h"
#include "openssl/sha.h"

int hash_to_bytes(uint8_t *input_buf, int input_len, uint8_t *output_buf, int hash_len, uint8_t hash_prefix)
{
	SHA256_CTX sha2;
	int i, new_input_len = input_len + 2; // extra byte for prefix
	uint8_t first_block = 0;
	uint8_t new_input[new_input_len+1];

	memset(new_input, 0, new_input_len+1);
	new_input[0] = first_block; // block number (always 0 by default)
	new_input[1] = hash_prefix; // set hash prefix
	memcpy((uint8_t *)(new_input+2), input_buf, input_len); // copy input bytes

	// prepare output buf
	memset(output_buf, 0, hash_len);

	if (hash_len <= SHA256_DIGEST_LENGTH) {
		SHA256_Init(&sha2);
		SHA256_Update(&sha2, new_input, new_input_len);
		uint8_t md[SHA256_DIGEST_LENGTH+1];
		SHA256_Final(md, &sha2);
		memcpy(output_buf, md, hash_len);
	}
	else {
		// apply variable-size hash technique to get desired size
		// determine block count.
		int blocks = (int) ceil(((double) hash_len) / SHA256_DIGEST_LENGTH);
		uint8_t md[SHA256_DIGEST_LENGTH+1];
		uint8_t md2[(blocks * SHA256_DIGEST_LENGTH)+1];
		uint8_t *target_buf = md2;
		for(i = 0; i < blocks; i++) {
			/* compute digest = SHA-2( i || prefix || input_buf ) || ... || SHA-2( n-1 || prefix || input_buf ) */
			target_buf += (i * SHA256_DIGEST_LENGTH);
			new_input[0] = (uint8_t) i;
			SHA256_Init(&sha2);
			SHA256_Update(&sha2, new_input, new_input_len);
			SHA256_Final(md, &sha2);
			memcpy(target_buf, md, hash_len);
			memset(md, 0, SHA256_DIGEST_LENGTH);
		}
		// copy back to caller
		memcpy(output_buf, md2, hash_len);
	}
	return 1;
}

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
	G1::G1(const Pairing &e, string data,
		unsigned short len): G(e){
			if(elementPresent) {
				element_init_G1(g, *(pairing_t*)&e.getPairing());
				int hash_len = 20;
				uint8_t hash_buf[hash_len];
				memset(hash_buf, 0, hash_len);
				int result = hash_to_bytes((uint8_t *) data.c_str(), len, hash_buf, hash_len, 2);
				if(!result)
					throw UndefinedPairingException();
				element_from_hash(g, hash_buf, hash_len);
			} else throw UndefinedPairingException();
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
