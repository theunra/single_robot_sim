
(cl:in-package :asdf)

(defsystem "nubot_common-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "VelCmd" :depends-on ("_package_VelCmd"))
    (:file "_package_VelCmd" :depends-on ("_package"))
  ))