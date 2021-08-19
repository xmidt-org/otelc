# Meson build file
#
# SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC
# SPDX-License-Identifier: Apache-2.0

project('otelc', 'c',
        version: '0.0.1',
        license: ['Apache-2.0'],
        default_options: ['c_std=c99',
                          'b_coverage=true'])

if not meson.is_subproject()
  # We want strict flags
  warning_level = 3   # -Wall
  werror = true
endif

################################################################################
# Common variable definitions
################################################################################

inc_base = 'include/'+meson.project_name()

################################################################################
# Generate the version header file
################################################################################

subdir('include/'+meson.project_name())

################################################################################
# Define the dependencies
################################################################################

# none

################################################################################
# Define the libraries
################################################################################

inc = include_directories(['include'])

install_headers([inc_base+'/common.h',
                 inc_base+'/metrics.h',
                 inc_base+'/time.h',
                 inc_base+'/tracing.h',
                 ver_h],
                 subdir: meson.project_name())

sources = ['src/empty.c']

libotelc = library(meson.project_name(),
                  sources,
                  include_directories: inc,
                  dependencies: [],
                  install: true)

################################################################################
# Define the examples
################################################################################
if not meson.is_subproject()
  examples = []

  foreach e : examples
    executable(e, ['examples/basic/'+e+'.c'], 
               include_directories: inc,
               dependencies: [],
               link_with: libotelc)
  endforeach
endif

################################################################################
# Define the tests
################################################################################

if not meson.is_subproject()
  test_args = ['-fprofile-arcs', '-ftest-coverage', '-O0']
  cunit_dep = dependency('cunit')

  tests = {}

  foreach test, vals : tests
    if 'opt' in vals and not get_option(vals['opt'])
      message('Skipping test: \u001b[1m'+test+'\u001b[0m ('+vals['opt']+' not enabled)')
    else
      deps = [cunit_dep]
      if 'deps' in vals
      deps += vals['deps']
      endif
      test(test,
           executable(test, vals['srcs'],
                      dependencies: deps,
                      install: false,
                      link_args: test_args))
    endif
  endforeach

  add_test_setup('valgrind',
                 is_default: true,
                 exe_wrapper: [ 'valgrind',
                                '--leak-check=full',
                                '--error-exitcode=1' ],
                 timeout_multiplier: 2)
endif

################################################################################
# Add the license check target
################################################################################

reuse_bin = find_program('reuse', required: false)
if reuse_bin.found()
  custom_target('license',
                command: [reuse_bin, 'lint'],
                build_always_stale: true,
                output: ['license'])
endif

libotelc_dep = declare_dependency(include_directories: ['include'],
                                          link_with: libotelc)

if meson.version().version_compare('>=0.54.0')
  meson.override_dependency(meson.project_name(), libotelc_dep)
endif
