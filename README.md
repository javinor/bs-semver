# bs-semver

Bindings for [the official NPM semver package](https://www.npmjs.com/package/semver)

## Usage

TODO

## Notes

Many functions accept an `options` argument which is either a boolean or an object and both default to:
```js
{
  loose: false,
  includePrerelease: false
}
```

This is not supported in this bindings module, and might be implement in the future (maybe)

# Process

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
* not implement compareLoose


