;(defmacro STARTDIR (&optional subdir)
  ;(let ((%x% (gensym "%x%->subdir")))
    ;`(let ((,%x% ,subdir))
       ;(if (not (null ,%x%))
           ;(format nil "../~A" ,%x%)
           ;(STARTDIR "")))))

(defun STARTDIR (&optional subdir &key :as-macro)
  (let ((body '(if (not (null subdir))
                   ;; concatenate two strings, which represent filesystem locations
                   (format nil "../~A" subdir)
                   (STARTDIR ""))))
    (if (not (null as-macro))
        (macrolet ((STARTDIR (&optional subdir)
                     ,body))
          (STARTDIR subdir))
        (unquote body))))

(defun __asdf-version__ ()
  (when (find-package :asdf)
    (let ((ver (symbol-value
                 (or (find-symbol (string :*asdf-version*) :asdf)
                     (find-symbol (string :*asdf-revision*) :asdf)))))
      (etypecase ver
        (string ver)
        (cons (with-output-to-string (s)
                (loop for (n . m) on ver
                      do (princ n s)
                      (when m (princ "." s)))))
        (null "1.0")))))
