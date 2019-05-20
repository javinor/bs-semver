[@bs.module "semver"] [@bs.val]
external clean: string => Js.nullable(string) = "clean";

[@bs.module "semver"] [@bs.val]
external validRange: string => Js.nullable(string) = "validRange";

/* === Versions === */

module Version = {
  type t = string;
  let toString = v => v;
  let parse = str => clean(str) |> Js.Nullable.toOption;
  let parseExn = str => parse(str) |> Belt.Option.getExn;
};

[@bs.module "semver"] [@bs.val]
external compare: (Version.t, Version.t) => int = "compare";

[@bs.module "semver"] [@bs.val]
external rcompare: (Version.t, Version.t) => int = "rcompare";

[@bs.module "semver"] [@bs.val]
external gt: (Version.t, Version.t) => bool = "gt";

[@bs.module "semver"] [@bs.val]
external gte: (Version.t, Version.t) => bool = "gte";

[@bs.module "semver"] [@bs.val]
external lt: (Version.t, Version.t) => bool = "lt";

[@bs.module "semver"] [@bs.val]
external lte: (Version.t, Version.t) => bool = "lte";

[@bs.module "semver"] [@bs.val]
external eq: (Version.t, Version.t) => bool = "eq";

[@bs.module "semver"] [@bs.val]
external neq: (Version.t, Version.t) => bool = "neq";

[@bs.module "semver"] [@bs.val]
external sortInPlace: array(Version.t) => array(Version.t) = "sort";

[@bs.module "semver"] [@bs.val]
external rsortInPlace: array(Version.t) => array(Version.t) = "rsort";

/* === Identifiers === */

type release =
  | Major
  | Minor
  | Patch
  | Premajor
  | Preminor
  | Prepatch
  | Prerelease;

let release_of_string = str =>
  switch (str) {
  | "major" => Major
  | "minor" => Minor
  | "patch" => Patch
  | "premajor" => Premajor
  | "preminor" => Preminor
  | "prepatch" => Prepatch
  | "prerelease" => Prerelease
  | _ => Js.Exn.raiseError("unable to convert unrecognized release")
  };

[@bs.module "semver"] [@bs.val]
external diff: (Version.t, Version.t) => Js.Nullable.t(string) = "diff";
let diff = (v1, v2) =>
  diff(v1, v2)
  |> Js.Nullable.toOption
  |> Belt.Option.map(_, release_of_string);

/* === Ranges === */

module Range = {
  type t = string;
  let toString = r => r;
  let parse = str => validRange(str) |> Js.Nullable.toOption;
  let parseExn = str => parse(str) |> Belt.Option.getExn;
};

[@bs.module "semver"] [@bs.val]
external satisfies: (Version.t, Range.t) => bool = "satisfies";

[@bs.module "semver"] [@bs.val]
external minSatisfying: (array(Version.t), Range.t) => Js.nullable(Version.t) =
  "minSatisfying";
let minSatisfying = (versions, range) =>
  minSatisfying(versions, range) |> Js.Nullable.toOption;

[@bs.module "semver"] [@bs.val]
external maxSatisfying: (array(Version.t), Range.t) => Js.nullable(Version.t) =
  "maxSatisfying";
let maxSatisfying = (versions, range) =>
  maxSatisfying(versions, range) |> Js.Nullable.toOption;