// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/views/test/combobox_test_api.h"

#include "ui/base/models/menu_model.h"
#include "ui/views/controls/combobox/combobox.h"
#include "ui/views/controls/menu/menu_runner.h"
#include "ui/views/controls/menu/menu_runner_handler.h"
#include "ui/views/test/menu_runner_test_api.h"

namespace views {
namespace test {
namespace {

// An dummy implementation of MenuRunnerHandler to check if the dropdown menu is
// shown or not.
class TestMenuRunnerHandler : public MenuRunnerHandler {
 public:
  explicit TestMenuRunnerHandler(int* show_counter)
      : show_counter_(show_counter) {}
  MenuRunner::RunResult RunMenuAt(Widget* parent,
                                  MenuButton* button,
                                  const gfx::Rect& bounds,
                                  MenuAnchorPosition anchor,
                                  ui::MenuSourceType source_type,
                                  int32 types) override {
    *show_counter_ += 1;
    return MenuRunner::NORMAL_EXIT;
  }

 private:
  int* show_counter_;

  DISALLOW_COPY_AND_ASSIGN(TestMenuRunnerHandler);
};

}  // namespace

void ComboboxTestApi::PerformActionAt(int index) {
  menu_model()->ActivatedAt(index);
}

void ComboboxTestApi::InstallTestMenuRunner(int* menu_show_count) {
  combobox_->menu_runner_.reset(
      new MenuRunner(menu_model(), MenuRunner::COMBOBOX));
  test::MenuRunnerTestAPI test_api(combobox_->menu_runner_.get());
  test_api.SetMenuRunnerHandler(
      make_scoped_ptr(new TestMenuRunnerHandler(menu_show_count)));
}

gfx::Size ComboboxTestApi::content_size() {
  return combobox_->content_size_;
}

ui::MenuModel* ComboboxTestApi::menu_model() {
  return combobox_->menu_model_adapter_.get();
}

}  // test
}  // views
