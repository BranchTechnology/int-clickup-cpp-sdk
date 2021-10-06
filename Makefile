build:
	docker build . -t clickup:base --target base

build-test: ## this will build a dev version of the shelf container
	docker run -it --network="host" clickup:test

run-build-test: ## runs the test exe inside of the container
	docker run -it --network="host" clickup:base sh -c /dir/build/test/clickup_test
	
run-test: ## runs the test exe inside of the container
	docker run -it --entrypoint test clickup:test

run-bash: ## this will bash into the container after compilation to allow debugging
	docker run -it --network="host" --entrypoint bash clickup:base

clang-format:
	find . -name "*.h" -o -name "*.cpp" -o -name "*.cc" -o -name "*.hxx" -o -name "*.cxx" -o -name "*.inl" -o -name "*.c" | xargs clang-format -style=file -i

.PHONY: help
help:           ## Show this help.
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
