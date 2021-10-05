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

run-test-env:
	docker-compose up -d localstack

run-test: ## this will build a dev version of the shelf container
	docker-compose run test_env

down: ## shut down docker-compose
	docker-compose down

.PHONY: help
help:           ## Show this help.
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'