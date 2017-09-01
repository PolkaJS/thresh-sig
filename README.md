# thresh-sig [![travis][travis-image]][travis-url] [![npm][npm-image]][npm-url] [![downloads][downloads-image]][downloads-url] [![Greenkeeper badge](https://badges.greenkeeper.io/PolkaJS/thresh-sig.svg)](https://greenkeeper.io/)

[travis-image]: https://travis-ci.org/PolkaJS/thresh-sig.svg?branch=master
[travis-url]: https://travis-ci.org/PolkaJS/thresh-sig
[npm-image]: https://img.shields.io/npm/v/@polkajs/thresh-sig.svg
[npm-url]: https://npmjs.org/package/@polkajs/thresh-sig
[downloads-image]: https://img.shields.io/npm/dm/@polkajs/thresh-sig.svg
[downloads-url]: https://npmjs.org/package/@polkajs/thresh-sig

## About

### Whitepapers

* [Threshold Signatures](http://www.shoup.net/papers/thsig.pdf)
* [Pairing Based Cryptography](https://crypto.stanford.edu/pbc/)
* [Intro to PBC](https://www.math.uwaterloo.ca/~ajmeneze/publications/pairings.pdf)
* [Intro to ECC](http://andrea.corbellini.name/2015/05/17/elliptic-curve-cryptography-a-gentle-introduction/)
* [Gap-Diffie-Hellman](https://eprint.iacr.org/2002/118.pdf)
* [Gap-Diffie-Hellman2](http://www.cc.gatech.edu/~aboldyre/papers/b.pdf)

## Use
```js
// NPM
npm install --save @polkajs/thresh-sig
// YARN
yarn add @polkajs/thresh-sig
```

## Install

**Linux Dependencies**
```
sudo apt-get install libgmp3-dev bison
sudo apt-get install python-pip python-dev libffi-dev libssl-dev libxml2-dev libxslt1-dev libjpeg8-dev zlib1g-dev
```

**OS X** (be sure to have xcode installed)
```
brew install openssl
```

**PBC**
```
wget https://crypto.stanford.edu/pbc/files/pbc-0.5.14.tar.gz
tar -xvf pbc-0.5.14.tar.gz
cd pbc-0.5.14
./configure ; make ; sudo make install
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

**BUILD**
```
npm run compile
```

---

## Example

```
const Threshsig = require('@polkajs/thresh-sig');

const threshsig = new Threshsig();
threshsig.deal(10, 5);
threshsig.encrypt("TEST");
console.log("verify ciphertext", threshsig.verifyCipherText());

const shares = threshsig.dealer.SKs.map((SK, i) => threshsig.decryptShare(i));
console.log("decrypted shares", shares);
const verifiedShares = shares.map((share, i) => threshsig.verifyShare(i));
console.log("verified Shares", verifiedShares);

// As long as you have at least k decrypted shares, you can obtain the original message:
const shareMap = {};
for (let i = 0; i < k; i++) {
  let n;
  while (shares[n] == null)
    n = Math.floor(Math.random() * shares.length);
  shareMap[n] = shares[n];
  shares[n] = null;
}
console.log("shareMap", shareMap);
const _m = CombineShares(C, Object.keys(shareMap), Object.values(shareMap));
console.log("m === _m", m === _m);
```

## API

### Types
```
type C = {
  U: string,
  V: string,
  W: string
}

type Deal = {
  secret: string,
  SKs:    Array<string>,
  VK:     string,
  VKs:    Array<string>
}
```

### Class ThresholdSignature

`new ThresholdSignature()`

#### deal(players: number, k: number): Deal
 * players: number of p2p in the network
 * k: threshold limit, minimum number of players needed to decode the shards
 * **return**: Deal (type)

#### encrypt(m: string | buffer): C
  * m: message to decrypt
    - if a 64 byte buffer or string, this IS the key
    - otherwise the message is encoded prior to use
    - **return**: C (type)

#### verifyCipherText(): bool
  * checks that C is authentic

#### decryptShare(i: number, share?: string): string
  * i: index of the share
  * share: a share to be added at index i
  * **return**: string (the decrypted share)

#### verifyShare(i: number, key?: string, share?: string): bool
  * i: index of the share
  * key: verification key to be added at index i
  * share: decrypted share to be added at index i
  * **return**: bool (true if the share is authentic, false otherwise)

#### combineShares(): string
  * **return**: the combined decrypted shares (the original message)

#### getShare(i: number): string
  * i: index of the share
  * **return**: string (the share)

#### setShare(i: number, share: string): bool
  * i: index of where to set the share
  * share: string of the share in question
  * **return**: true if successful, false otherwise

#### getVerificationKey(i: number): string
  * i: index of the verification key
  * **return**: the verification key at index i

#### setVerificationKey(i: number, key: string): bool
  * i: index of where to set the verification key
  * key: string of the verification key
  * **return**: true if successful, false otherwise

#### setC(c: C): C
  * c: (type C) merge values with current c
  * **return**: newly merged c

#### setG(g: string): bool
  * g: string of the G1 value
  * **return**: true if successful, false otherwise

## ISC License (ISC)

Copyright 2017 <PolkaJS>
Copyright (c) 2004-2010 by Internet Systems Consortium, Inc. ("ISC")
Copyright (c) 1995-2003 by Internet Software Consortium


Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
