open Jest;
open Semver;

let getExn = x => x |> Js.Nullable.toOption |> Belt.Option.getExn;

describe("Semver", () => {
  open Expect;

  test("SEMVER_SPEC_VERSION", () =>
    expect(Semver.semver_spec_version) |> toBe("2.0.0")
  );

  describe(".valid", () => {
    test("converts a valid version string to a Version.t", () =>
      expect(valid("1.2.3") |> getExn |> Version.show) |> toBe("1.2.3")
    );

    test("returns null for an invalid version", () =>
      expect(valid("qweqwe")) |> toBe(Js.Nullable.null)
    );
  });

  describe(".clean", () => {
    test("wraps and cleans a valid version in a Version.t", () =>
      expect(clean("  =v1.2.3  ") |> getExn |> Version.show)
      |> toBe("1.2.3")
    );

    test("returns null for an invalid version", () =>
      expect(clean("qweqwe")) |> toBe(Js.Nullable.null)
    );
  });

  describe(".inc", () => {
    test("bump version to next major release", () => {
      let version = valid("1.2.3-alpha.7") |> getExn;
      expect(inc(version, `Major, ()) |> Version.show) |> toBe("2.0.0");
    });

    test("bump version to next major release and down to pre-release", () => {
      let version = valid("1.2.3-alpha.7") |> getExn;
      expect(inc(version, `Premajor, ~identifier="beta", ()) |> Version.show)
      |> toBe("2.0.0-beta.0");
    });

    test("bump version to next minor release", () => {
      let version = valid("1.2.3-alpha.7") |> getExn;
      expect(inc(version, `Minor, ()) |> Version.show) |> toBe("1.3.0");
    });

    test("bump version to next minor release and down to pre-release", () => {
      let version = valid("1.2.3-alpha.7") |> getExn;
      expect(inc(version, `Preminor, ~identifier="beta", ()) |> Version.show)
      |> toBe("1.3.0-beta.0");
    });

    test("bump version to next patch release", () => {
      let version = valid("1.2.3-alpha.7") |> getExn;
      expect(inc(version, `Patch, ()) |> Version.show) |> toBe("1.2.3");
    });

    test("bump version to next patch release and down to pre-release", () => {
      let version = valid("1.2.3-alpha.7") |> getExn;
      expect(inc(version, `Prepatch, ~identifier="beta", ()) |> Version.show)
      |> toBe("1.2.4-beta.0");
    });

    test("bump version to next pre-release", () => {
      let version = valid("1.2.3-alpha.7") |> getExn;
      expect(inc(version, `Prerelease, ()) |> Version.show)
      |> toBe("1.2.3-alpha.8");
    });
  });

  describe(".diff", () => {
    test("returns null if versions are equal", () => {
      let v = valid("1.2.3-alpha.7") |> getExn;
      expect(diff(v, v)) |> toBe(Js.Nullable.null);
    });

    test("return difference in major versions", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("2.0.0") |> getExn;
      expect(diff(v1, v2) |> getExn) |> toBe(`Major);
    });
  });

  describe(".major", () =>
    test("returns the major identifier", () => {
      let v = valid("1.2.3-alpha.7") |> getExn;
      expect(major(v)) |> toBe("1");
    })
  );

  describe(".minor", () =>
    test("returns the minor identifier", () => {
      let v = valid("1.2.3-alpha.7") |> getExn;
      expect(minor(v)) |> toBe("2");
    })
  );

  describe(".patch", () =>
    test("returns the patch identifier", () => {
      let v = valid("1.2.3-alpha.7") |> getExn;
      expect(patch(v)) |> toBe("3");
    })
  );

  describe(".prerelease", () =>
    test("returns the pre-release identifier", () => {
      let v = valid("1.2.3-alpha.7") |> getExn;
      expect(prerelease(v)) |> toEqual([|"alpha", "7"|]);
    })
  );

  describe(".compareIdentifiers", () => {
    test("returns LT when lhs is smaller than rhs", () =>
      expect(compareIdentifiers("1", "2")) |> toEqual(LT)
    );

    test("returns EQ when lhs is equal to rhs", () =>
      expect(compareIdentifiers("2", "2")) |> toEqual(EQ)
    );

    test("returns GT when lhs is larger than rhs", () =>
      expect(compareIdentifiers("3", "2")) |> toEqual(GT)
    );
  });

  describe(".rcompareIdentifiers", () => {
    test("returns GT when lhs is smaller than rhs", () =>
      expect(rcompareIdentifiers("1", "2")) |> toEqual(GT)
    );

    test("returns EQ when lhs is equal to rhs", () =>
      expect(rcompareIdentifiers("2", "2")) |> toEqual(EQ)
    );

    test("returns LT when lhs is larger than rhs", () =>
      expect(rcompareIdentifiers("3", "2")) |> toEqual(LT)
    );
  });

  describe(".compare", () => {
    test("returns LT when lhs is smaller than rhs", () => {
      let v1 = valid("1.2.0") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(compare(v1, v2)) |> toEqual(LT);
    });

    test("returns EQ when lhs is equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(compare(v1, v2)) |> toEqual(EQ);
    });

    test("returns GT when lhs is larger than rhs", () => {
      let v1 = valid("1.2.9") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(compare(v1, v2)) |> toEqual(GT);
    });
  });

  describe(".rcompare", () => {
    test("returns GT when lhs is smaller than rhs", () => {
      let v1 = valid("1.2.0") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(rcompare(v1, v2)) |> toEqual(GT);
    });

    test("returns EQ when lhs is equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(rcompare(v1, v2)) |> toEqual(EQ);
    });

    test("returns LT when lhs is larger than rhs", () => {
      let v1 = valid("1.2.9") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(rcompare(v1, v2)) |> toEqual(LT);
    });
  });

  describe(".sortInPlace", () =>
    test("sorts an array of versions in ascending order", () => {
      let versions = [|
        valid("1.2.3") |> getExn,
        valid("1.7.7") |> getExn,
        valid("1.0.0") |> getExn,
      |];

      expect(sortInPlace(versions) |> Js.Array.map(Version.show))
      |> toEqual([|"1.0.0", "1.2.3", "1.7.7"|]);
    })
  );

  describe(".rsortInPlace", () =>
    test("sorts an array of versions in descending order", () => {
      let versions = [|
        valid("1.2.3") |> getExn,
        valid("1.7.7") |> getExn,
        valid("1.0.0") |> getExn,
      |];

      expect(rsortInPlace(versions) |> Js.Array.map(Version.show))
      |> toEqual([|"1.7.7", "1.2.3", "1.0.0"|]);
    })
  );

  describe(".gt", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.0.0") |> getExn;
      expect(gt(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.7.7") |> getExn;
      expect(gt(v1, v2)) |> toBe(false);
    });
  });

  describe(".gte", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.0.0") |> getExn;
      expect(gte(v1, v2)) |> toBe(true);
    });

    test("returns true if lhs is equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(gte(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.7.7") |> getExn;
      expect(gte(v1, v2)) |> toBe(false);
    });
  });

  describe(".lt", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.7.7") |> getExn;
      expect(lt(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.0.0") |> getExn;
      expect(lt(v1, v2)) |> toBe(false);
    });
  });

  describe(".lte", () => {
    test("returns true if lhs is greater than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.7.7") |> getExn;
      expect(lte(v1, v2)) |> toBe(true);
    });

    test("returns true if lhs is equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(lte(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is smaller than rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.0.0") |> getExn;
      expect(lte(v1, v2)) |> toBe(false);
    });
  });

  describe(".eq", () => {
    test("returns true if lhs is equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(eq(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is not equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.7.7") |> getExn;
      expect(eq(v1, v2)) |> toBe(false);
    });
  });

  describe(".neq", () => {
    test("returns true if lhs is not equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.7.7") |> getExn;
      expect(neq(v1, v2)) |> toBe(true);
    });

    test("returns false if lhs is equal to rhs", () => {
      let v1 = valid("1.2.3") |> getExn;
      let v2 = valid("1.2.3") |> getExn;
      expect(neq(v1, v2)) |> toBe(false);
    });
  });

  describe(".validRange", () => {
    test("converts a valid range string to a Range.t", () =>
      expect(validRange("~1.2.3") |> getExn |> Range.show)
      |> toBe(">=1.2.3 <1.3.0")
    );

    test("returns null for an invalid range", () =>
      expect(valid("qweqwe")) |> toBe(Js.Nullable.null)
    );
  });

  describe(".satisfies", () => {
    test("returns true when version is in range", () => {
      let range = validRange("1.2.7 || >=1.2.9 <2.0.0") |> getExn;
      let version = valid("1.4.6") |> getExn;
      expect(satisfies(version, range)) |> toBe(true);
    });

    test("returns false when version is not in range", () => {
      let range = validRange("1.2.7 || >=1.2.9 <2.0.0") |> getExn;
      let version = valid("1.2.8") |> getExn;
      expect(satisfies(version, range)) |> toBe(false);
    });
  });

  describe(".minSatisfying", () => {
    test("returns the min version in range", () => {
      let range = validRange("1.2") |> getExn;
      let versions =
        [|"1.2.3", "1.2.4"|] |> Array.map(str => str |> valid |> getExn);

      expect(minSatisfying(versions, range) |> getExn |> Version.show)
      |> toBe("1.2.3");
    });

    test("returns null if no version is in range", () => {
      let range = validRange("1.3") |> getExn;
      let versions =
        [|"1.2.3", "1.2.4"|] |> Array.map(str => str |> valid |> getExn);
      expect(minSatisfying(versions, range)) |> toBe(Js.Nullable.null);
    });
  });

  describe(".maxSatisfying", () => {
    test("returns the max version in range", () => {
      let range = validRange("1.2") |> getExn;
      let versions =
        [|"1.2.3", "1.2.4"|] |> Array.map(str => str |> valid |> getExn);

      expect(maxSatisfying(versions, range) |> getExn |> Version.show)
      |> toBe("1.2.4");
    });

    test("returns null if no version is in range", () => {
      let range = validRange("1.3") |> getExn;
      let versions =
        [|"1.2.3", "1.2.4"|] |> Array.map(str => str |> valid |> getExn);
      expect(maxSatisfying(versions, range)) |> toBe(Js.Nullable.null);
    });
  });
});