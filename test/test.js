const test = require('tape');
const { Dealer, Encrypt, VerifyCipherText, DecryptShare, VerifyShare, CombineShares } = require('../build/Release/addon.node'); // native c/c++

test('timing test', function (t) {
    t.plan(1);

    const str = "TEST", players = 10, k = 5;
    const m = require("crypto").createHash("sha256").update(str).digest().toString("hex");
    const dealer = Dealer(players, k);
    const C = Encrypt("TEST", dealer.VK);
    const verifyCipherText = VerifyCipherText(C);
    const shares = dealer.SKs.map((SK) => DecryptShare(C, SK));
    const verifiedShares = shares.map((share, i) => VerifyShare(C, share, dealer.VKs[i]));
    // As long as you have at least k decrypted shares, you can obtain the original message:
    const shareMap = {};
    // get k shares a random:
    for (let i = 0; i < k; i++) {
      let n;
      while (shares[n] == null)
        n = Math.floor(Math.random() * shares.length);
      shareMap[n] = shares[n];
      shares[n] = null;
    }
    const _m = CombineShares(C, Object.keys(shareMap), Object.values(shareMap));

    t.equal(m, _m, "decrypted shares are the same as the original message");
});
