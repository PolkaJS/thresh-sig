//@flow
const {
  CombineShares, Dealer, DecryptShare, Encrypt,
  SetG, VerifyCipherText, VerifyShare // $FlowFixMe
} = require('../build/Release/addon.node');
import extend from 'extend';

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

export default class ThresholdSignature {
  c:      C;
  dealer: Deal;
  DK: { [key: number]: string }; // Decrypted Key

  deal(players: number = 10, k: number = 5) {
    return this.dealer = Dealer(players, k);
  }

  encrypt(m: string | Buffer) {
    if (Buffer.isBuffer(m))
      m = m.toString();
    return this.c = Encrypt(m, this.dealer.VK);
  }

  verifyCipherText() {
    return VerifyCipherText(this.c);
  }

  decryptShare(i: number, share?: string) {
    if (share)
      this.dealer.SKs[i] = share;
    return this.DK[i] = DecryptShare(this.c, this.dealer.SKs[i]);
  }

  verifyShare(i: number, key?: string, share?: string) {
    if (share)
      this.dealer.SKs[i] = share;
    if (key)
      this.dealer.VKs[i] = key;
    return this.dealer.VKs[i] = VerifyShare(this.c, this.dealer.SKs[i], this.dealer.VKs[i]);
  }

  combineShares() {
    return CombineShares(this.c, Object.keys(this.DK), Object.values(this.DK));
  }

  getShare(i: number) {
    return this.dealer.SKs[i];
  }

  setShare(i: number, share: string) {
    this.dealer.SKs[i] = share;
    return true;
  }

  getVerificationKey(i: number) {
    return this.dealer.VKs[i];
  }

  setVerificationKey(i: number, key: string) {
    this.dealer.VKs[i] = key;
    return true;
  }

  setC(c: C) {
    return this.c = extend(this.c, c);
  }
}
