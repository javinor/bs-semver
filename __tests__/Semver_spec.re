open Jest;
module SV = Semver;
module Version = Semver.Version;
module Range = Semver.Range;

describe("Semver", () => {
  open Expect;

  describe("Version", () => {
    describe(".parse", () => {
      test("converts a valid version string to an optional Version.t", () =>
        expect(
          Version.parse("  =v1.2.3  ")
          |> Belt.Option.getExn
          |> Version.toString,
        )
        |> toBe("1.2.3")
      );

      test("returns None for an invalid version", () =>
        expect(Version.parse("qweqwe")) |> toBe(None)
      );
    });

    describe(".parseExn", () => {
      test("converts a valid version string to a Version.t", () =>
        expect(Version.parseExn("  =v1.2.3  ") |> Version.toString)
        |> toBe("1.2.3")
      );

      test("throws an error for an invalid version", () =>
        expect(() =>
          Version.parseExn("qweqwe")
        ) |> toThrow
      );
    });
  });

  describe(".compare", () => {
    test("returns LT when lhs is smaller than rhs", () => {
      let v1 = Version.parseExn("1.2.0");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.compare(v1, v2)) |> toEqual(-1);
    });

    test("returns EQ when lhs is equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.compare(v1, v2)) |> toEqual(0);
    });

    test("returns GT when lhs is larger than rhs", () => {
      let v1 = Version.parseExn("1.2.9");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.compare(v1, v2)) |> toEqual(1);
    });
  });

  describe(".rcompare", () => {
    test("returns GT when lhs is smaller than rhs", () => {
      let v1 = Version.parseExn("1.2.0");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.rcompare(v1, v2)) |> toEqual(1);
    });

    test("returns EQ when lhs is equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.rcompare(v1, v2)) |> toEqual(0);
    });

    test("returns LT when lhs is larger than rhs", () => {
      let v1 = Version.parseExn("1.2.9");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.rcompare(v1, v2)) |> toEqual(-1);
    });
  });

  describe(".sortInPlace", () =>
    test("sorts an array of versions in ascending order", () => {
      let versions = [|
        Version.parseExn("1.2.3"),
        Version.parseExn("1.7.7"),
        Version.parseExn("1.0.0"),
      |];

      expect(SV.sortInPlace(versions) |> Js.Array.map(Version.toString))
      |> toEqual([|"1.0.0", "1.2.3", "1.7.7"|]);
    })
  );

  describe(".rsortInPlace", () =>
    test("sorts an array of versions in descending order", () => {
      let versions = [|
        Version.parseExn("1.2.3"),
        Version.parseExn("1.7.7"),
        Version.parseExn("1.0.0"),
      |];

      expect(SV.rsortInPlace(versions) |> Js.Array.map(Version.toString))
      |> toEqual([|"1.7.7", "1.2.3", "1.0.0"|]);
    })
  );

  describe(".gt", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.0.0");
      expect(SV.gt(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.7.7");
      expect(SV.gt(v1, v2)) |> toBe(false);
    });
  });

  describe(".gte", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.0.0");
      expect(SV.gte(v1, v2)) |> toBe(true);
    });

    test("returns true if lhs is equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.gte(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.7.7");
      expect(SV.gte(v1, v2)) |> toBe(false);
    });
  });

  describe(".lt", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.7.7");
      expect(SV.lt(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.0.0");
      expect(SV.lt(v1, v2)) |> toBe(false);
    });
  });

  describe(".lte", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.7.7");
      expect(SV.lte(v1, v2)) |> toBe(true);
    });

    test("returns true if lhs is equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.lte(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.0.0");
      expect(SV.lte(v1, v2)) |> toBe(false);
    });
  });

  describe(".eq", () => {
    test("returns true if lhs is equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.eq(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is not equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.7.7");
      expect(SV.eq(v1, v2)) |> toBe(false);
    });
  });

  describe(".neq", () => {
    test("returns true if lhs is not equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.7.7");
      expect(SV.neq(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is equal to rhs", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("1.2.3");
      expect(SV.neq(v1, v2)) |> toBe(false);
    });
  });

  describe(".diff", () => {
    test("returns None if versions are equal", () => {
      let v = Version.parseExn("1.2.3-alpha.7");
      expect(SV.diff(v, v)) |> toBe(None);
    });

    test("return difference in major versions", () => {
      let v1 = Version.parseExn("1.2.3");
      let v2 = Version.parseExn("2.0.0");
      expect(SV.diff(v1, v2)) |> toBe(Some(SV.Major));
    });
  });

  describe("Range", () => {
    describe(".parse", () => {
      test("converts a valid range string to an optional Range.t", () =>
        expect(
          Range.parse("  ~1.2.3  ") |> Belt.Option.getExn |> Range.toString,
        )
        |> toBe(">=1.2.3 <1.3.0")
      );

      test("returns None for an invalid range", () =>
        expect(Range.parse("qweqwe")) |> toBe(None)
      );
    });

    describe(".parseExn", () => {
      test("converts a valid range string to a Range.t", () =>
        expect(Range.parseExn("  ~1.2.3  ") |> Range.toString)
        |> toBe(">=1.2.3 <1.3.0")
      );

      test("throws an error for an invalid version", () =>
        expect(() =>
          Range.parseExn("qweqwe")
        ) |> toThrow
      );
    });
  });

  describe(".satisfies", () => {
    test("returns true when version is in range", () => {
      let range = Range.parseExn("1.2.7 || >=1.2.9 <2.0.0");
      let version = Version.parseExn("1.4.6");
      expect(SV.satisfies(version, range)) |> toBe(true);
    });

    test("returns false when version is not in range", () => {
      let range = Range.parseExn("1.2.7 || >=1.2.9 <2.0.0");
      let version = Version.parseExn("1.2.8");
      expect(SV.satisfies(version, range)) |> toBe(false);
    });
  });

  describe(".minSatisfying", () => {
    test("returns the min version in range", () => {
      let range = Range.parseExn("1.2");
      let versions = [|
        Version.parseExn("1.2.3"),
        Version.parseExn("1.2.4"),
      |];
      expect(
        SV.minSatisfying(versions, range)
        |> Belt.Option.getExn
        |> Version.toString,
      )
      |> toBe("1.2.3");
    });

    test("returns None if no version is in range", () => {
      let range = Range.parseExn("1.3");
      let versions = [|
        Version.parseExn("1.2.3"),
        Version.parseExn("1.2.4"),
      |];
      expect(SV.minSatisfying(versions, range)) |> toBe(None);
    });
  });

  describe(".maxSatisfying", () => {
    test("returns the max version in range", () => {
      let range = Range.parseExn("1.2");
      let versions = [|
        Version.parseExn("1.2.3"),
        Version.parseExn("1.2.4"),
      |];
      expect(
        SV.maxSatisfying(versions, range)
        |> Belt.Option.getExn
        |> Version.toString,
      )
      |> toBe("1.2.4");
    });

    test("returns None if no version is in range", () => {
      let range = Range.parseExn("1.3");
      let versions = [|
        Version.parseExn("1.2.3"),
        Version.parseExn("1.2.4"),
      |];
      expect(SV.maxSatisfying(versions, range)) |> toBe(None);
    });
  });
});