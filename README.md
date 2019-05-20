# bs-semver

Bindings for [the official NPM semver package](https://www.npmjs.com/package/semver)

## Usage

Do the bindings dance:

```
npm install --save @jvnr/bs-semver
npm install --save semver
```

in `bsconfig.json`:
```json
{
  ...
  "bs-dependencies": ["@jvnr/bs-semver"]
}
```

## Notes

The API exposed by these bindings is adapted to be ergonomic in ReasonML (imho).

TL;DR

The API exposed by this bindings differs from the original NPM module. I originally wrote it as a one-to-one translation of the NPM module, but after consuming these bindings for a different projects I realised that it must differ. e.g. Some functions were not implemented, the `Semver` object is not exposed since I never needed it, etc.

Credits due to [Dmytro Gladkyi](https://github.com/gladimdim/bs-semver) for his [`bs-semver`](https://github.com/gladimdim/bs-semver) and article on [creating bindings for NPM packages](https://itnext.io/reasonml-create-bindings-for-npm-package-b8a3c6d0703e)


## Questions and Forks in the Road

What to do with functions that accept `options` argument? It is either a boolean or an object and both default to:
```js
{
  loose: false,
  includePrerelease: false
}
```

* How to write bindings? `semver spec`
* Testing
  * compilation errors because `{}` were in omitted in describe
  * plugin doesn't work in `__tests__` folder
  * Should I test bindings? How?
* Create a Version module?
* `valid` / `clean` - to support `options`?
* `inc`
  * How to support `release`s? as `string`? sum type?
  * `identifier` optional type vs. two `external`s
* `diff` returns `release` but also `null` if versions are equal
  * model this with `Js.Nullable.t` - how can I extend the polymorphic type?
* How to handle return value of `prerelease('1.2.3-alpha.7')`? or `major` / `minor` / `patch`?
* support `loose` flag for functions? `major` / `minor` / `patch` / etc.
* not implement `compareLoose`
* not implement `cmp`
* create module for Range
* stop implementing



