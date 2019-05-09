[@bs.module "semver"] [@bs.val]
external semver_spec_version: string = "SEMVER_SPEC_VERSION";

module Version: {
  type t;
  let show: t => string;
} = {
  type t = string;
  let show = v => v;
};

[@bs.deriving {jsConverter: newType}]
type release = [
  | [@bs.as "major"] `Major
  | [@bs.as "minor"] `Minor
  | [@bs.as "patch"] `Patch
  | [@bs.as "premajor"] `Premajor
  | [@bs.as "preminor"] `Preminor
  | [@bs.as "prepatch"] `Prepatch
  | [@bs.as "prerelease"] `Prerelease
];

[@bs.deriving {jsConverter: newType}]
type ordering =
  | [@bs.as (-1)] LT
  | [@bs.as 0] EQ
  | [@bs.as 1] GT;

[@bs.module "semver"] [@bs.val]
external valid: string => Js.nullable(Version.t) = "valid";

[@bs.module "semver"] [@bs.val]
external clean: string => Js.nullable(Version.t) = "clean";

[@bs.module "semver"] [@bs.val]
external inc: (Version.t, abs_release, string) => Version.t = "inc";
let inc = (v, r, ~identifier="", ()) => inc(v, releaseToJs(r), identifier);

[@bs.module "semver"] [@bs.val]
external diff: (Version.t, Version.t) => Js.Nullable.t(abs_release) = "diff";
let diff = (v1, v2) =>
  diff(v1, v2) |> Js.Nullable.bind(_, (. r) => releaseFromJs(r));

[@bs.module "semver"] [@bs.val] external major: Version.t => int = "major";
let major = v => major(v) |> string_of_int;

[@bs.module "semver"] [@bs.val] external minor: Version.t => int = "minor";
let minor = v => minor(v) |> string_of_int;

[@bs.module "semver"] [@bs.val] external patch: Version.t => int = "patch";
let patch = v => patch(v) |> string_of_int;

[@bs.module "semver"] [@bs.val]
external prerelease: Version.t => array(string) = "prerelease";
let prerelease = v =>
  prerelease(v) |> Js.Array.joinWith(".") |> Js.String.split(".");

[@bs.module "semver"] [@bs.val]
external compareIdentifiers: (string, string) => abs_ordering =
  "compareIdentifiers";
let compareIdentifiers = (id1, id2) =>
  compareIdentifiers(id1, id2) |> orderingFromJs;

[@bs.module "semver"] [@bs.val]
external rcompareIdentifiers: (string, string) => abs_ordering =
  "rcompareIdentifiers";
let rcompareIdentifiers = (id1, id2) =>
  rcompareIdentifiers(id1, id2) |> orderingFromJs;

[@bs.module "semver"] [@bs.val]
external compare: (Version.t, Version.t) => abs_ordering = "compare";
let compare = (v1, v2) => compare(v1, v2) |> orderingFromJs;

[@bs.module "semver"] [@bs.val]
external rcompare: (Version.t, Version.t) => abs_ordering = "rcompare";
let rcompare = (v1, v2) => rcompare(v1, v2) |> orderingFromJs;

[@bs.module "semver"] [@bs.val]
external sortInPlace: array(Version.t) => array(Version.t) = "sort";

[@bs.module "semver"] [@bs.val]
external rsortInPlace: array(Version.t) => array(Version.t) = "rsort";

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

/*
 === remaining semver keys: ===
 'parse',
 'SemVer',

 'cmp',
 'Comparator',
 'Range',
 'toComparators',
 'satisfies',
 'maxSatisfying',
 'minSatisfying',
 'minVersion',
 'validRange',
 'ltr',
 'gtr',
 'outside',
 'intersects',
 'coerce'
  */