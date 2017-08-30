const { Dealer, Encrypt, VerifyCipherText, DecryptShare, VerifyShare, CombineShares } = require('./build/Release/addon'); // native c/c++

const str = "TEST", players = 10, k = 5;
const m = require("crypto").createHash("sha256").update(str).digest().toString("hex");
console.log("m", m);

const dealer = Dealer(players, k);
console.log("dealer", dealer);
const C = Encrypt("TEST", dealer.VK);
console.log("C", C);
const verifyCipherText = VerifyCipherText(C);
console.log("Verify", verifyCipherText);
const shares = dealer.SKs.map((SK) => DecryptShare(C, SK));
console.log("decrypted shares", shares);
const verifiedShares = shares.map((share, i) => VerifyShare(C, share, dealer.VKs[i]));
console.log("verified Shares", verifiedShares);

// As long as you have at least 5 decrypted shares, you can obtain the original message:
const _m = CombineShares(C, shares.slice(0, 5));
console.log("m === _m", m === _m);
