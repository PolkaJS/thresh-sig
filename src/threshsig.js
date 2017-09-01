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
  c:       C;
  dealer:  Deal;
  DK:      { [key: number]: string }; // Decrypted Key
  players: number;
  k:       number

  deal(players: number = 10, k: number = 5): Deal {
    this.players = players;
    this.k       = k;
    return this.dealer = Dealer(players, k);
  }

  encrypt(m: string | Buffer): C {
    if (Buffer.isBuffer(m))
      m = m.toString();
    return this.c = Encrypt(m, this.dealer.VK);
  }

  verifyCipherText(): bool {
    return VerifyCipherText(this.c);
  }

  decryptShare(i: number, share?: string): string {
    if (share)
      this.dealer.SKs[i] = share;
    return this.DK[i] = DecryptShare(this.c, this.dealer.SKs[i]);
  }

  verifyShare(i: number, key?: string, share?: string): bool {
    if (share)
      this.dealer.SKs[i] = share;
    if (key)
      this.dealer.VKs[i] = key;
    return this.dealer.VKs[i] = VerifyShare(this.c, this.dealer.SKs[i], this.dealer.VKs[i]);
  }

  combineShares(): string {
    return CombineShares(this.c, Object.keys(this.DK), Object.values(this.DK));
  }

  getShare(i: number): string {
    return this.dealer.SKs[i];
  }

  setShare(i: number, share: string): bool {
    this.dealer.SKs[i] = share;
    return true;
  }

  getVerificationKey(i: number): string {
    return this.dealer.VKs[i];
  }

  setVerificationKey(i: number, key: string): bool {
    this.dealer.VKs[i] = key;
    return true;
  }

  setC(c: C): C {
    return this.c = extend(this.c, c);
  }

  setG(g: string): bool {
    SetG(g);
    return true;
  }
}
