/* === Versions === */

module Version: {
  type t;
  let toString: t => string;
  let parse: string => option(t);
  let parseExn: string => t;
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

type release =
  | Major
  | Minor
  | Patch
  | Premajor
  | Preminor
  | Prepatch
  | Prerelease;

let release_of_string: string => release;

let diff: (Version.t, Version.t) => option(release);

/* === Ranges === */

module Range: {
  type t;
  let toString: t => string;
  let parse: string => option(t);
  let parseExn: string => t;
};

[@bs.module "semver"] [@bs.val]
external satisfies: (Version.t, Range.t) => bool = "satisfies";

let minSatisfying: (array(Version.t), Range.t) => option(Version.t);

let maxSatisfying: (array(Version.t), Range.t) => option(Version.t);