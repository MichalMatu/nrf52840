# Tooling And Quality Gates

This project uses small, repeatable checks that work locally and in GitHub
Actions.

## Local tools

- PlatformIO Core builds and uploads the firmware.
- `clang-format` formats C/C++ source and board variant files.
- PlatformIO `pio check` runs static analysis. The default analyzer is Cppcheck.
- `pre-commit` runs the fast formatting gate before commit and the full
  PlatformIO quality gate before push.

## One-time setup

```sh
pre-commit install --hook-type pre-commit --hook-type pre-push
```

The hooks are optional but recommended. The same checks can always be run
manually.

## Daily commands

Format source files:

```sh
scripts/format.sh
```

Check formatting only:

```sh
scripts/format.sh --check
```

Run the full local gate:

```sh
scripts/quality.sh
```

Show firmware size:

```sh
scripts/size-report.sh
```

Upload remains explicit:

```sh
pio run -t upload
```

## CI gate

`.github/workflows/ci.yml` runs on pushes and pull requests to `main`.

The CI gate installs PlatformIO and `clang-format`, then runs:

```sh
scripts/quality.sh
```

## Static analysis policy

The project fails on medium and high severity defects. Low severity findings are
allowed for now because Arduino entry points and third-party libraries can
produce noisy style warnings.

Primary references:

- PlatformIO Static Code Analysis configuration:
  https://docs.platformio.org/en/latest/advanced/static-code-analysis/configuration.html
- PlatformIO `pio check` command:
  https://docs.platformio.org/en/latest/core/userguide/cmd_check.html
- PlatformIO GitHub Actions integration:
  https://docs.platformio.org/en/stable/integration/ci/github-actions.html
