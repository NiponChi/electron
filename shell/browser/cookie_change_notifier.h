// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_COOKIE_CHANGE_NOTIFIER_H_
#define SHELL_BROWSER_COOKIE_CHANGE_NOTIFIER_H_

#include <memory>

#include "base/callback_list.h"
#include "base/macros.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "services/network/public/mojom/cookie_manager.mojom.h"

namespace electron {

class AtomBrowserContext;
struct CookieDetails;

// Sends cookie-change notifications on the UI thread.
class CookieChangeNotifier : public network::mojom::CookieChangeListener {
 public:
  explicit CookieChangeNotifier(AtomBrowserContext* browser_context);
  ~CookieChangeNotifier() override;

  // Register callbacks that needs to notified on any cookie store changes.
  std::unique_ptr<base::CallbackList<void(const CookieDetails*)>::Subscription>
  RegisterCookieChangeCallback(
      const base::Callback<void(const CookieDetails*)>& cb);

 private:
  void StartListening();
  void OnConnectionError();

  // network::mojom::CookieChangeListener implementation.
  void OnCookieChange(const net::CanonicalCookie& cookie,
                      network::mojom::CookieChangeCause cause) override;

  AtomBrowserContext* browser_context_;
  base::CallbackList<void(const CookieDetails*)> cookie_change_sub_list_;

  mojo::Receiver<network::mojom::CookieChangeListener> receiver_;

  DISALLOW_COPY_AND_ASSIGN(CookieChangeNotifier);
};

}  // namespace electron

#endif  // SHELL_BROWSER_COOKIE_CHANGE_NOTIFIER_H_
