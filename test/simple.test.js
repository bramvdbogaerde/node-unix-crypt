const assert = require("assert")
const crypt = require("../index.js")

describe("crypt_gensalt", () => {
   it("should generate a salt for BCRYPT", () => {
      const answer = crypt.gensalt("$2b$", 5);
      assert(answer.length > 0);
   });

   it("should hash a password", () => {
      const setting = "$2b$05$ywTy3hys.Pe0eEn1YwcQA.";
      const answer = crypt.crypt("test", setting);
      assert(answer === "$2b$05$ywTy3hys.Pe0eEn1YwcQA.rdqsU3EKNqOk81NaKTXRNbnt9pfBeS.");
   });

   it("should correctly hash a password based on the stored value", () => {
      const setting = "$2b$05$ywTy3hys.Pe0eEn1YwcQA.rdqsU3EKNqOk81NaKTXRNbnt9pfBeS.";
      const answer = crypt.crypt("test", setting);
      assert(answer === "$2b$05$ywTy3hys.Pe0eEn1YwcQA.rdqsU3EKNqOk81NaKTXRNbnt9pfBeS.");
   })
});

