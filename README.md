# redwalk

[![Software License][ico-license]](LICENSE.md)
[![Build Status][ico-travis]][link-travis]

A C/C++ library and executable for network community detection.

## Install

``` bash
$ ./configure
$ cd release
$ make && make install
```

## Usage

``` bash
$ redwalk -o results.txt -k 2 -k 6 -i graph.edgelist
```

## Change log

Please see [CHANGELOG](CHANGELOG.md) for more information what has changed recently.

## Testing

``` bash
$ ./configure --enable-debug
$ cd debug
$ make && make test
```

## Credits

- [Peter Barr][link-author]
- [Dr. Kenneth Berenhaut][link-contributors]

## License

The MIT License (MIT). Please see [License File](LICENSE.md) for more information.

[ico-version]: https://img.shields.io/packagist/v/:vendor/:package_name.svg?style=flat-square
[ico-license]: https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat-square
[ico-travis]: https://img.shields.io/travis/:vendor/:package_name/master.svg?style=flat-square

[link-travis]: https://travis-ci.org/barrpet/redwalk
[link-author]: https://github.com/barrpet
[link-contributors]: http://college.wfu.edu/math
