#!/bin/sh

pane_id=$(wezterm cli get-pane-direction down)

if [ -z "${pane_id}" ]; then
  pane_id=$(wezterm cli split-pane)
fi

echo "$@" | wezterm cli send-text --pane-id $pane_id --no-paste
