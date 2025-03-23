# NoroDB
A LSM tree based key-value storage engine.

NoroDB is a fun project. It was never meant to be a production ready database engine.

# Usage
To make a build run:
```bash
make build
```
This command generates a static lib located under `./build/lib/norodb.a`. Link the library to you project.

Check the `examples/main.cc` to see an example how to use NoroDB.


