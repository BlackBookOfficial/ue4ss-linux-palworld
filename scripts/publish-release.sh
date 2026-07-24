#!/usr/bin/env bash
# Publishes a locally-built (WSL) libUE4SS.so as a GitHub release.
#
# This script does NOT build anything. Build first with:
#   cmake --build build_linux --target UE4SS
#
# It packages the already-built .so together with README.md and CHANGELOG.md,
# then publishes it as a release to BOTH:
#   - the source repo (XarminaEu/ue4ss-linux)
#   - the public builds repo (XarminaEu/-ue4ss-linux-builds)
#
# Requirements:
#   - gh CLI installed and authenticated: `gh auth login`
#   - Run from the repo root (or set REPO_ROOT below)
#
# Usage:
#   ./scripts/publish-release.sh

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

SOURCE_REPO="XarminaEu/ue4ss-linux"
BUILDS_REPO="XarminaEu/-ue4ss-linux-builds"
SO_PATH="build_linux/Game__Shipping__Linux64/lib/libUE4SS.so"
BUILDS_REPO_DIR="$REPO_ROOT/.builds-repo-checkout"

if ! command -v gh >/dev/null 2>&1; then
    echo "ERROR: gh CLI not found. Install it and run 'gh auth login' first." >&2
    exit 1
fi

if ! gh auth status >/dev/null 2>&1; then
    echo "ERROR: gh CLI is not authenticated. Run 'gh auth login' first." >&2
    exit 1
fi

if [ ! -f "$SO_PATH" ]; then
    echo "ERROR: $SO_PATH not found. Build it first with:" >&2
    echo "  cmake --build build_linux --target UE4SS" >&2
    exit 1
fi

echo "==> Packaging release..."
rm -rf release UE4SS-Linux-build.zip
mkdir -p release
cp "$SO_PATH" release/
cp README.md release/
cp CHANGELOG.md release/
(cd release && zip -r ../UE4SS-Linux-build.zip libUE4SS.so)

SHORT_SHA=$(git rev-parse --short HEAD)
DATE=$(date +'%Y-%m-%d')
TAG="v${DATE}-${SHORT_SHA}"
CHANGELOG_EXCERPT=$(awk '/^## /{found=1} found{print} /^---/{if(found)exit}' CHANGELOG.md | head -50)

echo "==> Publishing release $TAG to $SOURCE_REPO..."
gh release list --repo "$SOURCE_REPO" --json tagName --jq '.[].tagName' | while read -r tag; do
    echo "Deleting old release: $tag"
    gh release delete "$tag" --repo "$SOURCE_REPO" --yes --cleanup-tag
done
gh release create "$TAG" \
    --repo "$SOURCE_REPO" \
    --title "UE4SS Linux Build - ${DATE}" \
    --notes "${CHANGELOG_EXCERPT}" \
    UE4SS-Linux-build.zip
SOURCE_RELEASE_URL=$(gh release view "$TAG" --repo "$SOURCE_REPO" --json url --jq '.url')
echo "Source repo release: $SOURCE_RELEASE_URL"

echo "==> Syncing README/CHANGELOG and publishing release $TAG to $BUILDS_REPO..."
rm -rf "$BUILDS_REPO_DIR"
gh repo clone "$BUILDS_REPO" "$BUILDS_REPO_DIR" -- --quiet

cp README.md "$BUILDS_REPO_DIR/README.md"
cp CHANGELOG.md "$BUILDS_REPO_DIR/CHANGELOG.md"
mkdir -p "$BUILDS_REPO_DIR/docs"
cp -r docs/. "$BUILDS_REPO_DIR/docs/"
(
    cd "$BUILDS_REPO_DIR"
    git config user.name "UE4SS Release Publisher"
    git config user.email "release-publisher@local"
    git add README.md CHANGELOG.md docs
    if ! git diff --staged --quiet; then
        git commit -m "Update README, CHANGELOG and docs (${TAG})"
        git push
    else
        echo "No README/CHANGELOG/docs changes to push."
    fi
)

gh release list --repo "$BUILDS_REPO" --json tagName --jq '.[].tagName' | while read -r tag; do
    echo "Deleting old release: $tag"
    gh release delete "$tag" --repo "$BUILDS_REPO" --yes --cleanup-tag
done
gh release create "$TAG" \
    --repo "$BUILDS_REPO" \
    --title "UE4SS Linux Build - ${DATE}" \
    --notes "${CHANGELOG_EXCERPT}" \
    UE4SS-Linux-build.zip
BUILDS_RELEASE_URL=$(gh release view "$TAG" --repo "$BUILDS_REPO" --json url --jq '.url')
echo "Builds repo release: $BUILDS_RELEASE_URL"

echo "==> Done."
echo "Source repo:  $SOURCE_RELEASE_URL"
echo "Builds repo:  $BUILDS_RELEASE_URL"
