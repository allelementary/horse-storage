## Compile pure Yul with solc

```bash
solc --strict-assembly --optimize --optimize-runs 2000 ./yul/HorseStoreYul.yul --bin | grep 60
```

## Cast

```
cast to-base 0xe0 dec

cast to-base 0xe0 hex

cast to-base 0xe0 bin
```

## Get Gas Efficiency report

```
forge snapshot
```
