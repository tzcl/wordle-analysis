(def answers
  (->> (slurp "answers")
       (clojure.string/split-lines)))

(def words
  (->> (slurp "words")
       (clojure.string/split-lines)))

(->> words
     (filter #(re-matches #"..tt." %)))
