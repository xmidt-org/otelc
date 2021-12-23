<!--
SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC
SPDX-License-Identifier: Apache-2.0
-->
# otelc

A simple c implementation of OpenTelemetry's metrics, tracing and logging API.

[![Build Status](https://github.com/xmidt-org/otelc/workflows/CI/badge.svg)](https://github.com/xmidt-org/otelc/actions)
[![codecov.io](http://codecov.io/github/xmidt-org/otelc/coverage.svg?branch=main)](http://codecov.io/github/xmidt-org/otelc?branch=main)
[![Coverity](https://img.shields.io/coverity/scan/23236.svg)](https://scan.coverity.com/projects/xmidt-org-otelc)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=xmidt-org_otelc&metric=alert_status)](https://sonarcloud.io/dashboard?id=xmidt-org_otelc)
[![Language Grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/xmidt-org/otelc.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/xmidt-org/otelc/context:cpp)
[![Apache V2 License](http://img.shields.io/badge/license-Apache%20V2-blue.svg)](https://github.com/xmidt-org/otelc/blob/main/LICENSES/Apache-2.0.txt)
[![GitHub release](https://img.shields.io/github/release/xmidt-org/otelc.svg)](CHANGELOG.md)

This is a small and hopefully simple implementationn of OpenTelemetry's metrics,
tracing and logging APIs.  The goal of this code is to allow for providers to
either be built in or added later without impacting the code that uses this
library.

The target audience for this is generally embedded environments that are running
linux but don't have enough resources for larger implementations.

## Building and Testing Instructions

```
meson setup --warnlevel 3 --werror build
cd build
ninja all test coverage
firefox meson-logs/coveragereport/index.html
```
