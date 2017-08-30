# thresh-sig [![travis][travis-image]][travis-url] [![npm][npm-image]][npm-url] [![downloads][downloads-image]][downloads-url] [![Greenkeeper badge](https://badges.greenkeeper.io/PolkaJS/thresh-sig.svg)](https://greenkeeper.io/)

[travis-image]: https://travis-ci.org/PolkaJS/thresh-sig.svg?branch=master
[travis-url]: https://travis-ci.org/PolkaJS/thresh-sig
[npm-image]: https://img.shields.io/npm/v/@polkajs/thresh-sig.svg
[npm-url]: https://npmjs.org/package/@polkajs/thresh-sig
[downloads-image]: https://img.shields.io/npm/dm/@polkajs/thresh-sig.svg
[downloads-url]: https://npmjs.org/package/@polkajs/thresh-sig

## About

### Whitepapers
[Threshold Signatures](http://www.shoup.net/papers/thsig.pdf)
[Pairing Based Cryptography](https://crypto.stanford.edu/pbc/)
[Intro to PBC](https://www.math.uwaterloo.ca/~ajmeneze/publications/pairings.pdf)
[Intro to ECC](http://andrea.corbellini.name/2015/05/17/elliptic-curve-cryptography-a-gentle-introduction/)

## Use
`npm install --save @polkajs/thresh-sig`

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
`npm run compile`

---

## ISC License (ISC)

Copyright 2017 <PolkaJS>
Copyright (c) 2004-2010 by Internet Systems Consortium, Inc. ("ISC")
Copyright (c) 1995-2003 by Internet Software Consortium


Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
